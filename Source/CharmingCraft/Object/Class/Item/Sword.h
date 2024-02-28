// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Sword.generated.h"

class ASwordActor;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API USword : public UWeapon
{
	GENERATED_BODY()

private:


public:
	USword();

	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator, AActor* ItemActorEntity) override;
	virtual void OnWeaponUse() override;
	virtual void OnWeaponHit(UItemStack* WeaponHit, APawn* Instigator, AItemEntityActor* ItemActorEntity,
	                         AActor* HitEntity) override;
	virtual void EndItemInteract() override;
};
