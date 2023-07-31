// Fill out your copyright notice in the Description page of Project Settings.


#include "DExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ADExplosiveBarrel::ADExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true); // allows object can drop on the floor
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	// NO auto apply some force 
	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f;
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on the mass)
	ForceComp->bImpulseVelChange = true;

	// Optional, default constructor of component already add 4 object type to affect, excluding WordDynamic
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

/*!
 *	PostInitializeComponents() run before the @function BeginPlay(), avoid some strange hot reloading issues
 */
void ADExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComp->OnComponentHit.AddDynamic(this, &ADExplosiveBarrel::OnActorHit);
}

void ADExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse(); // Fire the impulse

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor),
	       GetWorld()->TimeSeconds)
	const FString CombineString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombineString, nullptr, FColor::Green, 2.0f, true);

	// Detailed information on logging in UE
	// logs-printing-message-to-yourself-during-runtime
}

// Called every frame
void ADExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
