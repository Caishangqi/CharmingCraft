// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "CharmingCraft/Object/Components/UI/DamageIndicator.h"


// Sets default values
AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	AttributeComponent = CreateDefaultSubobject<UDAttributeComponent>("Attribute Component");
	//DamageIndicator = CreateDefaultSubobject<UDamageIndicator>("DamageIndicator Component");
}

// Called when the game starts or when spawned
void AEntity::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEntity::Interact_Implementation(APawn* InstigatorPawn)
{
}

void AEntity::OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData)
{
	IDamageable::OnActionHit_Implementation(InstigatorPawn, HitData);
	AttributeComponent->DamageChain->HandleDamage(HitData);
}
