// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "CharmingCraft/Core/Container/Enum/EEquipmentSocket.h"
#include "Equipment.generated.h"

/**
 * 
 */
class AItemEntityActor;
class AEquipmentEntityActor;
UCLASS()
class CHARMINGCRAFT_API UEquipment : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Socket")
	EEquipmentSocket Socket;

	FTimerHandle TraceTimer;
	UPROPERTY()
	TObjectPtr<AEquipmentEntityActor> ItemEntityActor;
	UPROPERTY()
	APawn* Player;
	UPROPERTY()
	UItemStack* MappingItemStack;
	UPROPERTY()
	TSet<TObjectPtr<AActor>> HitActors;

public:
	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator) override;
	virtual void OnEquipmentDuringUse();
	virtual void OnEquipmentHit(UItemStack* EquipmentItemStack, APawn* Instigator, AActor* HitEntity);
	virtual void EndItemInteract() override;
};
