// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartSwordPommel.h"


// Sets default values for this component's properties
UEquipPartSwordPommel::UEquipPartSwordPommel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipPartSwordPommel::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEquipPartSwordPommel::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
