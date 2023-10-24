// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Object/Class/Item/Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UWeapon : public UItem
{
	GENERATED_BODY()

public:
	virtual void OnItemInteract(UItemStack* InteractItemStack, AActor* Instigator, AActor * ItemActorEntity) override;
	virtual void OnWeaponUse();
	virtual void OnWeaponHit(UItemStack* WeaponHit, AActor* Instigator, AActor * ItemActorEntity);
};
