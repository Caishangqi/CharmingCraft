// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentManagerComponent.h"

#include "EquipmentRenderComponent.h"
#include "EquipmentSlotComponent.h"
#include "CharmingCraft/Item/Equip/HelmetClass.h"

// Sets default values for this component's properties
UEquipmentManagerComponent::UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HelmetSlot = CreateDefaultSubobject<UEquipmentSlotComponent>("HelmetSlot");

	EquipmentRenderComponent = ObjectInitializer.CreateDefaultSubobject<UEquipmentRenderComponent>(
		this, "EquipmentRenderComponent");
}


// Called when the game starts
void UEquipmentManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEquipmentManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
