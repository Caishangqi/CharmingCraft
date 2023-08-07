// Fill out your copyright notice in the Description page of Project Settings.


#include "DInventoryComponent.h"

// Sets default values for this component's properties
UDInventoryComponent::UDInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}

void UDInventoryComponent::AddToInventory()
{
}

void UDInventoryComponent::RemoveFromInventory()
{
}


// Called when the game starts
void UDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UDInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
