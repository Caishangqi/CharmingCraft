// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DInventoryComponent.generated.h"


struct FItemStackData;
class UItemStack;
class UDataTable;
class ADPlayerAIController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdateIndex, int32, Index);

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

	/* 将物品添加到物品栏函数 ItemStack 版本 */
	virtual FReturnSuccessRemainQuantity AddToInventory(UItemStack* ItemStack);

	/* 将物品从到物品栏移除函数 ItemStack 版本 */
	UFUNCTION(BlueprintCallable)
	virtual void RemoveInventory(int32 Index, bool RemoveWholeStack, bool IsConsumed);
	/* 找到物品栏可以堆叠物品的slot ItemStack 版本 */
	UFUNCTION(BlueprintCallable)
	virtual int32 FindSlot(UItemStack* ItemID);
	/* 找到物品的最大叠加 ItemStack 版本*/
	virtual int32 GetMaxStackSize(UItemStack* ItemStack);
	/* 叠加同类物品 ItemStack 版本*/
	virtual void AddToStack(int32 Index, int32 Quantity, UItemStack* ItemStack);

	virtual FReturnValue IsEmptySlotAvailable();

	virtual bool CreateNewStack(UItemStack* ItemStack, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	virtual void TransferSlots(int32 SourceIndex, UDInventoryComponent* SourceInventory, int32 DestinationIndex);
	UFUNCTION(BlueprintCallable)
	virtual void Drop(UItemStack* ItemStack, int32 Quantity);

	virtual FVector GetDropLocation();

	/* Debug Function */
	virtual void PrintDebugMessage();
	static FVector RandomUnitVectorInConeInDegrees(const FVector& ConeDir, float ConeHalfAngleInDegrees);

	/* Editor Only */
	// virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PreloadMaterials")
	TArray<FItemStackData> PreloadMaterials;
	void InitializeItemStackWithMaterials();
	/* Event */

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdate OnInventoryUpdate;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdateIndex OnInventoryUpdateIndex;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 InventorySlotSelectIndex = 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Parameter")
	int InventorySize;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory Parameter")
	TArray<UItemStack*> Inventory; // Updated

	UPROPERTY(EditAnywhere, Category = "MaterialData")
	UDataTable* MaterialData; // Updated

	/* Local Variables */
	inline static bool bLocalHasFailed = false;
	int32 RFILocalQuantity;
	UPROPERTY(EditAnywhere, Category = "LocalItemStack")
	UItemStack* LocalItemStack;

	/* Replicated 确保只有服务器可以更改该属性，并且更改完毕后复制到客户端 */
	void OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator);

	virtual void PostInitProperties() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
