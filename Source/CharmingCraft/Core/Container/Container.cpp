// Fill out your copyright notice in the Description page of Project Settings.


#include "Container.h"

void AContainer::Interact_Implementation(APawn* InstigatorPawn)
{
}

AContainer::AContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}
