// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStack.h"

#include "CharmingCraft/Interface/Meta/HelmetMeta.h"

// Sets default values for this component's properties
UItemStack::UItemStack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ItemMeta = CreateDefaultSubobject<UItemMeta>("ItemMeta");
	// ...
}

UItemStack::UItemStack(const FDataTableRowHandle Type)
{
	Material = Type;
	Amount = 1;
}

UItemStack::UItemStack(FDataTableRowHandle Type, int32 Amount)
{
	Material = Type;
	this->Amount = Amount;
}


// Called when the game starts
void UItemStack::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UItemStack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
