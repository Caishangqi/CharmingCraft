// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActionActor.h"

#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "CharmingCraft/Core/Skill/Actions/NativeOnHitAction.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABaseActionActor::ABaseActionActor(): ActionActorHealth(1)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
	RootComponent = SceneComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile movement component");

	CollisionBox = CreateDefaultSubobject<USphereComponent>("Collision Box");
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetGenerateOverlapEvents(true);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseActionActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseActionActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABaseActionActor::BeginPlay()
{
	Super::BeginPlay();
}

bool ABaseActionActor::InjectActionData_Implementation(FActionActorData ActionActorData)
{
	ActionHitData = ActionActorData.ActionHitData;
	InstigatorAction = ActionActorData.InstigatorAction;
	ActionActorOwner = ActionActorData.ActionActorOwner;
	OnHitActions = ActionActorData.OnHitCastAction;
	OnSpawnActions = ActionActorData.OnSpawnCastAction;
	OnTickActions = ActionActorData.OnTickCastAction;
	Parent = ActionActorData.Parent;
	return true;
}


// Called every frame
void ABaseActionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseActionActor::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseActionActor::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                     bool bFromSweep, const FHitResult& SweepResult)
{
	// Usually execute OnActionActorHit_Implementation, but I lay down for users
}


bool ABaseActionActor::OnActionActorHit_Implementation(AActor* OtherActor)
{
	// Ensure the Same Action's Action not collied or interact with each other
	if (OtherActor->IsA(ABaseActionActor::StaticClass()))
	{
		// If they have the same InstigatorAction we return false indicate not to execute interface
		if (Cast<ABaseActionActor>(OtherActor)->InstigatorAction == this->InstigatorAction)
		{
			return false;
		}
		
	}
	
	if (OnHitActions && !IgnoreActors.Contains(OtherActor))
	{
		// If it is a valid UNativeOnHitAction
		TObjectPtr<UNativeOnHitAction> OnHitAction = Cast<UNativeOnHitAction>(OnHitActions);
		OnHitAction->TargetActor = OtherActor; // Set the target for UNativeOnHitAction
		OnHitAction->AppliedHitData = ActionHitData; // Set the HitData for UNativeOnHitAction
		OnHitAction->StartAction(ActionActorOwner);
		return true;
	}
	return false;
}

bool ABaseActionActor::OnActionActorDestroy_Implementation()
{
	return false;
}

void ABaseActionActor::OnActionActorTick_Implementation()
{
}

bool ABaseActionActor::OnActionActorSpawn_Implementation()
{
	return false;
}
