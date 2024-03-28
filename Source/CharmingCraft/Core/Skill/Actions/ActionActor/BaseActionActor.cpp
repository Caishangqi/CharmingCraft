// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActionActor.h"

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
}


bool ABaseActionActor::OnActionActorHit_Implementation()
{
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
