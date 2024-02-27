// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"
#include "EquipmentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipmentComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

	// 1st parameter is the index, second is slot allowed ItemMeta
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, TSubclassOf<UItemMeta>> EquipmentSlotAllowedType;

	UFUNCTION()
	void OnContainerItemTransferListener(UObject* Instigator, UInventoryComponent* SourceContainer, int32 SourceIndex,
	                                     UInventoryComponent* TargetContainer, int32 TargetIndex,
	                                     UItemStack* ItemBeingTransfer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void
	TransferSlots(int32 SourceIndex, UInventoryComponent* SourceInventory, int32 DestinationIndex) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
