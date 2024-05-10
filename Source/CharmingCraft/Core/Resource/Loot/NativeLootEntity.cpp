// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeLootEntity.h"

#include "CharmingCraft/Core/Resource/Lib/ResourceGenerateLibrary.h"


// Sets default values
ANativeLootEntity::ANativeLootEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LootContent = CreateDefaultSubobject<UInventoryComponent>("Loot Content");
	LootMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Loot Mesh Component");
}

void ANativeLootEntity::GenerateLootContent(TArray<UItemStack*> Content)
{
	LootContent->Inventory.SetNumUninitialized(Content.Num());
	for (int i = 0; i < Content.Num(); i++)
	{
		LootContent->Inventory[i] = Content[i];
	}
}

// Called when the game starts or when spawned
void ANativeLootEntity::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANativeLootEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

