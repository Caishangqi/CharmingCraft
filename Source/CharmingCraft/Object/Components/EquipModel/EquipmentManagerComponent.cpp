// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentManagerComponent.h"

#include "DCharacter.h"
#include "EquipmentRenderComponent.h"
#include "../ItemStack.h"

// Sets default values for this component's properties
UEquipmentManagerComponent::UEquipmentManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	InventorySize = 12;
	PrimaryComponentTick.bCanEverTick = true;
	Owner = Cast<ADCharacter>(GetOwner());
	EquipmentRenderComponent = CreateDefaultSubobject<UEquipmentRenderComponent>(
		"EquipmentRenderComponent")->Initialize(InventorySize, Owner);


	/*
	 * 主手 0
	 * 副手 1
	 * 未指定 2
	 * 主动物品 I 3
	 * 主动物品 II 4
	 * 主动物品 III 5
	 * 主动物品 III 6
	 * 盔甲 头盔 7
	 * 盔甲 胸甲 8
	 * 盔甲 护腿 9
	 * 盔甲 靴子 10
	 */
}

void UEquipmentManagerComponent::PostInitProperties()
{
	Super::PostInitProperties();
	Inventory.SetNum(InventorySize);
}


// Called when the game starts
void UEquipmentManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UEquipmentManagerComponent::OnRegister()
{
	Super::OnRegister();
	OnEquipUpdate.AddDynamic(EquipmentRenderComponent, &UEquipmentRenderComponent::UpdateRender);
}

void UEquipmentManagerComponent::TransferSlots(int32 SourceIndex, UDInventoryComponent* SourceInventory,
                                               int32 DestinationIndex)
{
	Super::TransferSlots(SourceIndex, SourceInventory, DestinationIndex);
	OnEquipUpdate.Broadcast(DestinationIndex);
}


// Called every frame
void UEquipmentManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEquipmentManagerComponent::IsOccupied(UItemStack* Slot)
{
	if (Slot == nullptr)
	{
		return false;
	}
	return true;
}
