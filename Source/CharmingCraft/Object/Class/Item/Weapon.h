// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "../Object/Class/Item/Item.h"
#include "Weapon.generated.h"
class AItemEntityActor;
class ASwordEntityActorP5;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UWeapon : public UEquipment
{
	GENERATED_BODY()

protected:
	/* 计时器 */
	FTimerHandle SwordTraceTimer;
	UPROPERTY()
	ASwordEntityActorP5* SwordActor;
	UPROPERTY()
	APawn* Player;
	UPROPERTY()
	UItemStack* MappingItemStack;
	UPROPERTY()
	TSet<AActor*> HitActors;

public:
	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator, AActor* ItemActorEntity) override;
	virtual void OnWeaponUse();
	virtual void OnWeaponHit(UItemStack* WeaponHit, APawn* Instigator, AItemEntityActor* ItemActorEntity, AActor* HitEntity);
	virtual void EndItemInteract() override;
};
