// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"
#include "EquipmentComponent.generated.h"

class UGameEventHandler;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipmentComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

	// 1st parameter is the index, second is slot allowed ItemMeta
	UPROPERTY(EditAnywhere, BlueprintReadWrite) // Editor Modified Only
	TMap<int32, TSubclassOf<UItemMeta>> EquipmentSlotAllowedType;

	UFUNCTION()
	void OnContainerItemTransferListener(UObject* Instigator, UInventoryComponent* SourceContainer, int32 SourceIndex,
	                                     UInventoryComponent* TargetContainer, int32 TargetIndex,
	                                     UItemStack* ItemBeingTransfer);

	UFUNCTION(BlueprintCallable)
	bool UpdateEquipmentModelToEntity(UObject* Instigator, UInventoryComponent* SourceContainer,
	                                  int32 SourceIndex,
	                                  UInventoryComponent* TargetContainer, int32 TargetIndex,
	                                  UItemStack* ItemBeingTransfer);
	/*!
	 * Create ItemEntityActor and attach to specify socket, no
	 * duplication attachment check
	 * @param UpdateIndex The updated index in the EquipmentComponent
	 * @return whether or not is successful
	 */
	UFUNCTION(BlueprintCallable)
	bool AttachNewEquipmentModelToEntity(int32 UpdateIndex);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGameEventHandler> GameEventHandler;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TransferSlots(int32 SourceIndex, UInventoryComponent* SourceInventory, int32 DestinationIndex) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnEquipment(UObject* Instigator, UItemStack* OnEquipItem, int32 EquipIndex);
	UFUNCTION(BlueprintCallable)
	virtual void UnEquipment(UObject* Instigator, UItemStack* UnEquipItem, int32 EquipIndex);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
