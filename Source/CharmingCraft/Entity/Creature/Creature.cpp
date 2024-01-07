// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

#include "CharmingCraft/Object/Components/UI/DamageIndicator.h"


// Sets default values
ACreature::ACreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreatureAttributeComponent = CreateDefaultSubobject<UDAttributeComponent>("Creature Attribute Component");
	DamageIndicator = CreateDefaultSubobject<UDamageIndicator>("DamageIndicator");
	DamageIndicator->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACreature::OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData)
{
	IDamageable::OnActionHit_Implementation(InstigatorPawn, HitData);
}
