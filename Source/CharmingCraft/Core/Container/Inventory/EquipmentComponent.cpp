// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "../Core/Item/Meta/ItemMeta.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"


// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEquipmentComponent::OnContainerItemTransferListener(UObject* Instigator, UInventoryComponent* SourceContainer,
                                                          int32 SourceIndex,
                                                          UInventoryComponent* TargetContainer, int32 TargetIndex,
                                                          UItemStack* ItemBeingTransfer)
{
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Event Listener at UGameEventHandler::OnContainerItemTransferEvent()"));
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UGameEventHandler> GameEventHandler = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance())->
		GetGameEventHandler();
	GameEventHandler->OnContainerItemTransfer.AddDynamic(this, &UEquipmentComponent::OnContainerItemTransferListener);
	// ...
}

void UEquipmentComponent::TransferSlots(int32 SourceIndex, UInventoryComponent* SourceInventory, int32 DestinationIndex)
{
	/* Validation Check */
	// 注意: 这个时候在函数执行早期阶段,目标Container还没有被设置ItemStack,你必须拿到Source的待转移物品进行判断
	if (EquipmentSlotAllowedType.Find(DestinationIndex) && SourceInventory->Inventory[SourceIndex]->ItemMeta->IsA(
		EquipmentSlotAllowedType.Find(DestinationIndex)->Get()))
	{
		Super::TransferSlots(SourceIndex, SourceInventory, DestinationIndex);
	}
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
