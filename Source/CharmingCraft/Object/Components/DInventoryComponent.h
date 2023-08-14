// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Structs/FDSlotStruct.h"
#include "Components/ActorComponent.h"
#include "DInventoryComponent.generated.h"


struct FDItemStruct;
class UDataTable;
class ADPlayerAIController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	struct FReturnValue
	{
		int32 Index;
		bool Result;
	};

	struct FReturnSuccessRemainQuantity
	{
		bool bIsSuccess;
		int32 RemainQuantity;
	};

public:
	// Sets default values for this component's properties
	UDInventoryComponent();

	/* 将物品添加到物品栏函数 */
	virtual FReturnSuccessRemainQuantity AddToInventory(FString ItemID, int32 Quantity);
	/* 将物品从到物品栏移除函数 */
	UFUNCTION(BlueprintCallable)
	virtual void RemoveFromInventory(int32 Index, bool RemoveWholeStack, bool IsConsumed);
	/* 找到物品栏可以堆叠物品的slot */
	virtual int32 FindSlot(FString ItemID);
	/* 找到物品的最大叠加 */
	virtual int32 GetMaxStackSize(FString ItemID);

	virtual void AddToStack(int32 Index, int32 Quantity, FString ItemID);

	virtual FReturnValue AnyEmptySlotAvailable();

	virtual bool CreateNewStack(FString ItemID, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	virtual void TransferSlots(int32 SourceIndex, UDInventoryComponent* SourceInventory, int32 DestinationIndex);

	UFUNCTION(BlueprintCallable)
	virtual void DropItem(FString ItemID, int32 Quantity);

	virtual FVector GetDropLocation();

	virtual FDItemStruct* GetItemData(FString ItemID);
	/* Debug Function */
	virtual void PrintDebugMessage();
	static FVector RandomUnitVectorInConeInDegrees(const FVector& ConeDir, float ConeHalfAngleInDegrees);

	/* Event */

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdate OnInventoryUpdate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Parameter")
	int InventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Parameter")
	TArray<FDSlotStruct> Content;

	UPROPERTY(EditAnywhere, Category = "Data")
	UDataTable* ItemData;

	/* Local Variables */
	inline static bool bLocalHasFailed = false;
	int32 RFILocalQuantity;
	FString LocalItemID;

	FDSlotStruct LocalSlotContents;

	/* Replicated 确保只有服务器可以更改该属性，并且更改完毕后复制到客户端 */

	void OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
