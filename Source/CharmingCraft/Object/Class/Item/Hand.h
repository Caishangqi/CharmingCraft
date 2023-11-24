// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Hand.generated.h"

class ADCharacter;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UHand : public UWeapon
{
	GENERATED_BODY()

public:
	UHand();

	TObjectPtr<ADCharacter> Character;

	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator, AActor* ItemActorEntity) override;
	virtual void OnWeaponUse() override;
	virtual void OnWeaponHit(UItemStack* WeaponHit, APawn* Instigator, AActor* ItemActorEntity,
	                         AActor* HitEntity) override;
	virtual void EndItemInteract() override;
};
