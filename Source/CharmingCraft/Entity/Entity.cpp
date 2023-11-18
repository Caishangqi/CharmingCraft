// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "CharmingCraft/Object/Components/UI/DamageIndicator.h"


// Sets default values
AEntity::AEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// UE_LOG(LogTemp, Warning, TEXT("AEntity::AEntity() Create"));
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

void AEntity::BeginDestroy()
{
	Super::BeginDestroy();
	// UE_LOG(LogTemp, Error, TEXT("AEntity::BeginDestroy() Destroy"));
}

void AEntity::Interact_Implementation(APawn* InstigatorPawn)
{
}

void AEntity::OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData)
{
	IActionOnHitInterface::OnActionHit_Implementation(InstigatorPawn, HitData);
}


