// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeCreature.h"

#include "CharmingCraft/Core/Buff/BuffHandlerComponent.h"
#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "CharmingCraft/Core/UI/HealthIndicator.h"
#include "CharmingCraft/Object/Components/UI/DamageIndicator.h"


// Sets default values
ANativeCreature::ANativeCreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreatureAttributeComponent = CreateDefaultSubobject<UDAttributeComponent>("Creature Attribute Component");
	DamageIndicator = CreateDefaultSubobject<UDamageIndicator>("DamageIndicator");
	DamageIndicator->SetupAttachment(GetRootComponent());
	HealthIndicator = CreateDefaultSubobject<UHealthIndicator>("HealthIndicator");
	HealthIndicator->SetupAttachment(GetRootComponent());
	BuffHandlerComponent = CreateDefaultSubobject<UBuffHandlerComponent>("BuffHandlerComp");
	ActionComponent = CreateDefaultSubobject<UDActionComponent>("ActionComp");
}

// Called when the game starts or when spawned
void ANativeCreature::BeginPlay()
{
	Super::BeginPlay();
	/* Fix 2014/1/13 Bind Delegate multiply time when re stream the level */
	if (!CreatureAttributeComponent->OnHealthChanged.IsBound())
	{
		CreatureAttributeComponent->OnHealthChanged.AddDynamic(this, &ANativeCreature::HandleHealthChanged);
	}
}


// Called every frame
void ANativeCreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANativeCreature::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayTags;
	FGameplayTagContainer ComponentTags;
	ActionComponent->GetOwnedGameplayTags(ComponentTags);
	TagContainer.AppendTags(ComponentTags);
}


// Called to bind functionality to input
void ANativeCreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANativeCreature::OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData)
{
	if (!CreatureAttributeComponent->IsDead)
	{
		CreatureAttributeComponent->SubmitHitData(HitData);
		HitReaction(HitData.DamageResponse);
	}
}

void ANativeCreature::HandleDamageIndicator_Implementation(FHitData HitData)
{
	IUIProcess::HandleDamageIndicator_Implementation(HitData);
}

void ANativeCreature::HandleHealthChanged_Implementation(APawn* InstigatorPawn, UDAttributeComponent* OwningComp,
                                                   float Health, float HealthDelta)
{
	IDamageable::HandleHealthChanged_Implementation(InstigatorPawn, OwningComp, Health, HealthDelta);
}


void ANativeCreature::HandleDeath_Implementation(APawn* InstigatorPawn)
{
}

bool ANativeCreature::IsDead_Implementation()
{
	return CreatureAttributeComponent->IsDead;
}

void ANativeCreature::HitReaction_Implementation(EDamageResponse Response)
{
}
