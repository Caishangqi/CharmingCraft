// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "../Core/Item/Meta/ItemMeta.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Class/Item/Equipment.h"

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

	/* Update The Render of Equipment on socket call when Transfer successful */
	UpdateEquipmentModelToEntity(Instigator, SourceContainer, SourceIndex, TargetContainer, TargetIndex,
	                             ItemBeingTransfer);
}

bool UEquipmentComponent::UpdateEquipmentModelToEntity(UObject* Instigator, UInventoryComponent* SourceContainer,
                                                       int32 SourceIndex,
                                                       UInventoryComponent* TargetContainer, int32 TargetIndex,
                                                       UItemStack* ItemBeingTransfer)
{
	/* Update Other Slot, Delete or change */
	if (TargetContainer->IsA(UEquipmentComponent::StaticClass()))
	{
		if (Inventory[TargetIndex]->ItemMeta->ItemEntityActor)
		{
			Inventory[TargetIndex]->ItemMeta->ItemEntityActor->Destroy();
		}
	}
	else if (TargetContainer->IsA(UInventoryComponent::StaticClass()))
	{
		if (TargetContainer->Inventory[TargetIndex]->ItemMeta->ItemEntityActor)
		{
			TargetContainer->Inventory[TargetIndex]->ItemMeta->ItemEntityActor->Destroy();
		}
	}

	if (TargetContainer == SourceContainer)
	{
		if (Inventory[TargetIndex])
		{
			Inventory[TargetIndex]->ItemMeta->ItemEntityActor->Destroy();
		}

		if (Inventory[SourceIndex])
		{
			Inventory[SourceIndex]->ItemMeta->ItemEntityActor->Destroy();
		}

		AttachNewEquipmentModelToEntity(TargetIndex);
		AttachNewEquipmentModelToEntity(SourceIndex);
		return true;
	}

	return AttachNewEquipmentModelToEntity(TargetIndex);
}

bool UEquipmentComponent::AttachNewEquipmentModelToEntity(int32 UpdateIndex)
{
	if (Inventory[UpdateIndex])
	{
		TObjectPtr<UItemStack> EquipmentItemStack;
		EquipmentItemStack = Inventory[UpdateIndex];
		TObjectPtr<UEquipment> EquipmentClass = Cast<UEquipment>(EquipmentItemStack->ItemClass.GetDefaultObject());

		FString EquipmentSocket = StaticEnum<EEquipmentSocket>()->GetNameStringByValue(
			static_cast<int64>(EquipmentClass->Socket));

		if (EquipmentSocket == "HAND")
		{
			switch (UpdateIndex)
			{
			case 3:

				EquipmentSocket = FString("LEFT_").Append(EquipmentSocket);

				break;
			case 5:
				EquipmentSocket = FString("RIGHT_").Append(EquipmentSocket);
				break;
			default: break;
			}
		}

		TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = Cast<USkeletalMeshComponent>(
			this->GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));


		if (Inventory[UpdateIndex]->ItemMeta->IsA(UWeaponMeta::StaticClass()))
		{
			TObjectPtr<AItemEntityActor> AttachedActor = Inventory[UpdateIndex]->ItemMeta->CreateItemEntityActor(this);
			Inventory[UpdateIndex]->ItemMeta->ItemEntityActor = AttachedActor;

			AttachedActor->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::KeepRelativeTransform,
			                                 *EquipmentSocket);
			UE_LOG(LogChamingCraftGameEvent, Display,
			       TEXT("[📍]  Event Listener at UEquipmentComponent::UpdateEquipmentModelToEntity Socket = %s"),
			       *EquipmentSocket);
		}

		return true;
	}
	return false;
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

		/* Apply Equipment Attribute Through Event
		 *  - Use this Component to Store Equipment Attribute Separately and
		 *  pass the Attribute Data to Attribute Component when needed
		 */
	}
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
