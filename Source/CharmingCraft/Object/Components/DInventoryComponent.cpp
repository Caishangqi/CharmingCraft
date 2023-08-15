// Fill out your copyright notice in the Description page of Project Settings.


#include "DInventoryComponent.h"
#include "DItemDataComponent.h"
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

UDInventoryComponent::FReturnSuccessRemainQuantity UDInventoryComponent::AddToInventory(FString ItemID, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::AddToInventory %s | %d"), *ItemID, Quantity);
	FReturnSuccessRemainQuantity Result;
	int32 LocalQuantity = Quantity;
	while (LocalQuantity > 0 && !bLocalHasFailed)
	{
		int32 SlotIndex = FindSlot(ItemID);
		if (SlotIndex != -1)
		{
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

/*!
 * @param Index 移除物品栏序号位置
 * @param RemoveWholeStack 是否移除整组物品还只是一个
 * @param IsConsumed 是否是消耗物品
 */
void UDInventoryComponent::RemoveFromInventory(int32 Index, bool RemoveWholeStack, bool IsConsumed)
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::RemoveFromInventory Parameter: Index: %d| Quantity: %d"),
	       Index, Content[Index].Quantity);
	RFILocalQuantity = Content[Index].Quantity;
	LocalItemID = Content[Index].ItemID;

	// 4:49
	if (RFILocalQuantity == 1 || RemoveWholeStack)
	{
		Content[Index].Quantity = 0;
		Content[Index].ItemID = FString("None");
		if (IsConsumed)
		{
		}
		else
		{
			DropItem(LocalItemID, RFILocalQuantity);
		}
	}
	else
	{
		Content[Index].Quantity = Content[Index].Quantity - 1;
		if (IsConsumed)
		{
		}
		else
		{
			DropItem(LocalItemID, 1);
		}
	}
	OnInventoryUpdate.Broadcast();
}

int32 UDInventoryComponent::FindSlot(FString ItemID)
{
	for (int32 Index = 0; Index < Content.Num(); ++Index)
	{
		FDSlotStruct& Slot = Content[Index];
		bool bIDEqual = Slot.ItemID == ItemID;
		bool bQuantityValid = Slot.Quantity < GetMaxStackSize(ItemID);
		if (bIDEqual && bQuantityValid)
		{
			bLocalHasFailed = false;
			UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::FindSlot %d"), Index);
			return Index; // 返回找到的Index
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::FindSlot =  FALSE"));
	return -1; // 如果没有找到合适的Slot，返回-1或其他指示值
}

int32 UDInventoryComponent::GetMaxStackSize(FString ItemID)
{
	const FName RowName = FName(*ItemID);
	if (ItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Data IS NULL"));
	}
	if (FDItemStruct* Row = ItemData->FindRow<FDItemStruct>(RowName,TEXT("Looking up row in MyDataTable")))
	{
		UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::GetMaxStackSize HAVE ITEM DATA FOUND"));
		return Row->StackSize;
	}
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::GetMaxStackSize NO ITEM DATA FOUND"));
	return -1;
}

void UDInventoryComponent::AddToStack(int32 Index, int32 Quantity, FString ItemID)
{
	if (Content.IsValidIndex(Index))
	{
		Content[Index].ItemID = ItemID;
		Content[Index].Quantity = Content[Index].Quantity + Quantity;
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

bool UDInventoryComponent::CreateNewStack(FString ItemID, int32 Quantity)
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
			// Content 是箱子, Source 是玩家的背包
			int32 MaxStackSize = GetMaxStackSize(Content[DestinationIndex].ItemID);
			if (LocalSlotContents.Quantity + Content[DestinationIndex].Quantity > MaxStackSize)
			{
				// 优先算出背包剩余物品, 如果鼠标悬浮物品为 32 箱子里 64,则先计算背包
				// 计算如下 光标物品 - (最大堆叠数 - 同Index下的相同物品数量)
				// 32- (64 - 48) = 16
				SourceInventory->Content[SourceIndex].Quantity = LocalSlotContents.Quantity - (MaxStackSize - Content[
					DestinationIndex].Quantity);
				Content[DestinationIndex].Quantity = MaxStackSize;
			}
			else if (LocalSlotContents.Quantity + Content[DestinationIndex].Quantity <= MaxStackSize)
			{
				Content[DestinationIndex].Quantity = LocalSlotContents.Quantity + Content[
					SourceIndex].Quantity;
				SourceInventory->Content[SourceIndex].Quantity = 0;
				SourceInventory->Content[SourceIndex].ItemID = FString("None");
			}
			OnInventoryUpdate.Broadcast();
			SourceInventory->OnInventoryUpdate.Broadcast();
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

void UDInventoryComponent::DropItem(FString ItemID, int32 Quantity)
{
	int32 DIQuantity = Quantity;
	UClass* ActorClass = GetItemData(ItemID)->ItemClass;
	for (int32 Index = 0; Index < DIQuantity; ++Index)
	{
		GetWorld()->SpawnActor<AActor>(ActorClass, GetDropLocation(), FRotator3d(1.0));
	}
}

FVector UDInventoryComponent::GetDropLocation()
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	//
	FVector TraceStart = GetOwner()->GetActorLocation() + RandomUnitVectorInConeInDegrees(
		GetOwner()->GetActorForwardVector(), 30) * 150;
	FVector TraceEnd = TraceStart - FVector(0.0, 0.0, 500.0);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	return Hit.Location;
}


FDItemStruct* UDInventoryComponent::GetItemData(FString ItemID)
{
	FDItemStruct* Data = ItemData->FindRow<FDItemStruct>(FName(ItemID),TEXT("Looking up row in MyDataTable"));
	return Data;
}

void UDInventoryComponent::PrintDebugMessage()
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::PrintDebugMessage"));
	UE_LOG(LogTemp, Warning, TEXT("Content Size is %d"), Content.Num());
	for (int32 Index = 0; Index < Content.Num(); ++Index)
	{
		FDSlotStruct& Slot = Content[Index];
		FString DebugMessage = FString::Printf(
			TEXT("Index: %d | ItemID: %s | Quantity: %d"), Index, *Slot.ItemID, Slot.Quantity);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
	}
}

/*
 * 随机圆锥方向向量生成
 */
FVector UDInventoryComponent::RandomUnitVectorInConeInDegrees(const FVector& ConeDir, float ConeHalfAngleInDegrees)
{
	// 随机生成一个角度和方位角
	float RandAngle = FMath::RandRange(0.f, FMath::DegreesToRadians(ConeHalfAngleInDegrees));
	float RandAzimuth = FMath::RandRange(0.f, 2.f * PI);

	// 使用球坐标系生成随机向量
	FVector RandVector;
	RandVector.X = FMath::Sin(RandAngle) * FMath::Cos(RandAzimuth);
	RandVector.Y = FMath::Sin(RandAngle) * FMath::Sin(RandAzimuth);
	RandVector.Z = FMath::Cos(RandAngle);

	// 创建一个旋转，使Z轴对齐到指定的ConeDir
	FQuat AlignQuat = FQuat::FindBetweenNormals(FVector::UpVector, ConeDir);

	// 将随机向量旋转到指定的圆锥方向上
	FVector ResultVector = AlignQuat.RotateVector(RandVector);

	return ResultVector;
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
