// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Object/Class/Item/Item.h"
#include "CharmingCraft/Core/Entity/Item/model/SwordActor.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UWeapon : public UItem
{
	GENERATED_BODY()

protected:
	/* 计时器 */
	FTimerHandle SwordTraceTimer;
	UPROPERTY()
	ASwordActor* SwordActor;
	UPROPERTY()
	APawn* Player;
	UPROPERTY()
	UItemStack* MappingItemStack;
	UPROPERTY()
	TSet<AActor*> HitActors;

public:
	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator, AActor* ItemActorEntity) override;
	virtual void OnWeaponUse();
	virtual void OnWeaponHit(UItemStack* WeaponHit, APawn* Instigator, AActor* ItemActorEntity, AActor* HitEntity);
	virtual void EndItemInteract() override;
};
