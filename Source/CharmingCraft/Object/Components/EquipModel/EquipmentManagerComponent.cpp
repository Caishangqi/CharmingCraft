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
	EquipmentRenderComponent = CreateDefaultSubobject<UEquipmentRenderComponent>(
		"EquipmentRenderComponent");


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
	Inventory.SetNum(InventorySize);
	// ...
}

// Be careful with life time
void UEquipmentManagerComponent::OnRegister()
{
	Super::OnRegister();
	// This Event Bind is for transfer item in Equip inventory update
	OnEquipUpdate.AddDynamic(EquipmentRenderComponent, &UEquipmentRenderComponent::UpdateRender);
	// This Event Bind is for transfer item in Main inventory let equip inventory update
	HandleInventory->OnInventoryUpdateIndex.AddDynamic(EquipmentRenderComponent,
	                                                   &UEquipmentRenderComponent::UpdateRender);
	// Only in register phase the component will attach to player
	Owner = Cast<ADCharacter>(GetOwner());
	EquipmentRenderComponent->Initialize(InventorySize, Owner);
}


void UEquipmentManagerComponent::TransferSlots(int32 SourceIndex, UDInventoryComponent* SourceInventory,
                                               int32 DestinationIndex)
{
	Super::TransferSlots(SourceIndex, SourceInventory, DestinationIndex);
	OnEquipUpdate.Broadcast(DestinationIndex);
	UE_LOG(LogTemp, Warning, TEXT("UEquipmentManagerComponent::TransferSlots"));
}

UEquipmentManagerComponent* UEquipmentManagerComponent::Initialize(UDInventoryComponent* LinkInventory)
{
	this->HandleInventory = LinkInventory;
	return this;
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
