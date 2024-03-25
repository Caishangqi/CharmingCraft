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
	/*!
	 * Call OnEquip when the equipment is equipped on equip inventory
	 * @param Instigator Who Equip
	 * @param OnEquipItem The Item that equip on slot
	 */
	UFUNCTION(BlueprintCallable)
	virtual void OnEquip(UObject* Instigator, UItemStack* OnEquipItem);
	/*!
	 * Call UnEquip when equipment is UnEquipped from equip inventory
	 * @param Instigator Who UnEquip
	 * @param UnEquipItem The Item that UnEquip from slot
	 */
	UFUNCTION(BlueprintCallable)
	virtual void UnEquip(UObject* Instigator, UItemStack* UnEquipItem);
	/*!
	 * @Deprecated Move to ItemDynamicAbility System
	 * @param InteractItemStack 
	 * @param Instigator 
	 */
	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator) override;
	/*!
	 * @Deprecated Move to ItemDynamicAbility System
	 */
	virtual void OnEquipmentDuringUse();
	/*!
	 * @Deprecated Move to ItemDynamicAbility System
	 * @param EquipmentItemStack 
	 * @param Instigator 
	 * @param HitEntity 
	 */
	virtual void OnEquipmentHit(UItemStack* EquipmentItemStack, APawn* Instigator, AActor* HitEntity);
	/*!
	 * @Deprecated Move to ItemDynamicAbility System
	 */
	virtual void EndItemInteract() override;
};
