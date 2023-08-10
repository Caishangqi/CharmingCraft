// Fill out your copyright notice in the Description page of Project Settings.


#include "DInventoryComponent.h"

#include "DCharacter.h"
#include "DItemDataComponent.h"
#include "Algo/IndexOf.h"
#include "CharmingCraft/Controller/DPlayerAIController.h"
#include "CharmingCraft/Interface/DGameplayInterface.h"
#include "CharmingCraft/Interface/DItemInteractInterface.h"
#include "CharmingCraft/Object/Structs/FDItemStruct.h"

// Sets default values for this component's properties
UDInventoryComponent::UDInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	// ...
}

UDInventoryComponent::FReturnSuccessRemainQuantity UDInventoryComponent::AddToInventory(FName ItemID, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::AddToInventory %s | %d"), *ItemID.ToString(), Quantity);
	FReturnSuccessRemainQuantity Result;
	int32 LocalQuantity = Quantity;
	while (LocalQuantity > 0 && !bLocalHasFailed)
	{
		if (FindSlot(ItemID) != -1)
		{
			int32 SlotIndex = FindSlot(ItemID);
			AddToStack(SlotIndex, 1, ItemID);
			LocalQuantity--;
			UE_LOG(LogTemp, Warning, TEXT("AddToStack(SlotIndex, 1, ItemID);"));
		}
		else if (AnyEmptySlotAvailable().Result)
		{
			if (CreateNewStack(ItemID, 1))
			{
				LocalQuantity--;
			}
			else
			{
				bLocalHasFailed = true;
			}
		}
		else
		{
			bLocalHasFailed = true;
		}
	}
	Result.bIsSuccess = !bLocalHasFailed;
	Result.RemainQuantity = LocalQuantity;

	return Result;
}

void UDInventoryComponent::RemoveFromInventory()
{
}

int32 UDInventoryComponent::FindSlot(FName ItemID)
{
	for (int32 Index = 0; Index < Content.Num(); ++Index)
	{
		FDSlotStruct& Slot = Content[Index];
		bool bIDEqual = Slot.ItemID == ItemID;
		bool bQuantityValid = Slot.Quantity < GetMaxStackSize(ItemID);
		if (bIDEqual && bQuantityValid)
		{
			bLocalHasFailed = true;
			UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::FindSlot %d"), Index);
			return Index; // 返回找到的Index
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::FindSlot =  FALSE"));
	return -1; // 如果没有找到合适的Slot，返回-1或其他指示值
}

int32 UDInventoryComponent::GetMaxStackSize(FName ItemID)
{
	const FName RowName = FName(*ItemID.ToString());
	if (FDItemStruct* Row = ItemData->FindRow<FDItemStruct>(RowName,TEXT("Looking up row in MyDataTable")))
	{
		UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::GetMaxStackSize HAVE ITEM DATA FOUND"));
		return Row->StackSize;
	}
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::GetMaxStackSize NO ITEM DATA FOUND"));
	return -1;
}

void UDInventoryComponent::AddToStack(int32 Index, int32 Quantity, FName ItemID)
{
	if (Content.IsValidIndex(Index))
	{
		FDSlotStruct Slot;
		Slot.ItemID = ItemID;
		Slot.Quantity = Content[Index].Quantity + Quantity;
		Content.Insert(Slot, Index);
	}
}

UDInventoryComponent::FReturnValue UDInventoryComponent::AnyEmptySlotAvailable()
{
	//
	FReturnValue Result;
	for (int32 Index = 0; Index < Content.Num(); ++Index)
	{
		if (Content[Index].Quantity == 0)
		{
			Result.Index = Index;
			Result.Result = true;
			return Result;
		}
	}
	Result.Index = -1;
	Result.Result = false;
	return Result;
}

bool UDInventoryComponent::CreateNewStack(FName ItemID, int32 Quantity)
{
	if (AnyEmptySlotAvailable().Result)
	{
		FDSlotStruct Slot;
		Slot.ItemID = ItemID;
		Slot.Quantity = Quantity;

		Content[AnyEmptySlotAvailable().Index] = Slot;
		return true;
	}
	return false;
}

void UDInventoryComponent::TransferSlots(int32 SourceIndex, UDInventoryComponent* SourceInventory,
                                         int32 DestinationIndex)
{
	LocalSlotContents = SourceInventory->Content[SourceIndex];
	if (DestinationIndex < 0)
	{
	}
	else
	{
		// 发出者的背包Index
		if (Content[DestinationIndex].ItemID == LocalSlotContents.ItemID)
		{
		}
		else
		{
			SourceInventory->Content[SourceIndex] = Content[DestinationIndex];
			Content[DestinationIndex] = LocalSlotContents;
			//
			OnInventoryUpdate.Broadcast();
			SourceInventory->OnInventoryUpdate.Broadcast();
		}
	}
}

void UDInventoryComponent::PrintDebugMessage()
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::PrintDebugMessage"));
	UE_LOG(LogTemp, Warning, TEXT("Content Size is %d"), Content.Num());
	for (int32 Index = 0; Index < Content.Num(); ++Index)
	{
		FDSlotStruct& Slot = Content[Index];
		FString DebugMessage = FString::Printf(
			TEXT("Index: %d | ItemID: %s | Quantity: %d"), Index, *Slot.ItemID.ToString(), Slot.Quantity);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
	}
}


void UDInventoryComponent::OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator)
{
	if (TargetActor.Get()->GetComponentByClass(UDItemDataComponent::StaticClass()))
	{
		IDItemInteractInterface::Execute_Interact(
			TargetActor.Get()->GetComponentByClass(UDItemDataComponent::StaticClass()), Instigator);
	}

	UE_LOG(LogTemp, Warning, TEXT("Call Back from UDInventoryComponent::OnItemInteract"));
}

// Called when the game starts
void UDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// 设置背包大小
	Content.SetNum(InventorySize);
}


// Called every frame
void UDInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
