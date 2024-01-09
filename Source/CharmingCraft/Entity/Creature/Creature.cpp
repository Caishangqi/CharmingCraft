// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

#include "CharmingCraft/Core/UI/HealthIndicator.h"
#include "CharmingCraft/Object/Components/UI/DamageIndicator.h"


// Sets default values
ACreature::ACreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreatureAttributeComponent = CreateDefaultSubobject<UDAttributeComponent>("Creature Attribute Component");
	DamageIndicator = CreateDefaultSubobject<UDamageIndicator>("DamageIndicator");
	DamageIndicator->SetupAttachment(GetRootComponent());
	HealthIndicator = CreateDefaultSubobject<UHealthIndicator>("HealthIndicator");
	HealthIndicator->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	CreatureAttributeComponent->OnHealthChanged.AddDynamic(this, &ACreature::HandleHealthChanged);
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
	if (!CreatureAttributeComponent->IsDead)
	{
		CreatureAttributeComponent->DamageChain->HandleDamage(HitData);
		HitReaction(HitData.DamageResponse);
	}
}

void ACreature::HandleDamageIndicator_Implementation(FHitData HitData)
{
	IUIProcess::HandleDamageIndicator_Implementation(HitData);
}

void ACreature::HandleHealthChanged_Implementation(APawn* InstigatorPawn, UDAttributeComponent* OwningComp,
                                                   float Health, float HealthDelta)
{
	IDamageable::HandleHealthChanged_Implementation(InstigatorPawn, OwningComp, Health, HealthDelta);
}


void ACreature::HandleDeath_Implementation(APawn* InstigatorPawn)
{
}

bool ACreature::IsDead_Implementation()
{
	return CreatureAttributeComponent->IsDead;
}

void ACreature::HitReaction_Implementation(EDamageResponse Response)
{
}
