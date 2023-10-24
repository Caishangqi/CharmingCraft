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
	/* 计时器 */
	FTimerHandle SwordTraceTimer;
	UPROPERTY()
	ASwordActor* SwordActor;
	UPROPERTY()
	AActor* Player;
	UPROPERTY()
	UItemStack* MappingItemStack;

public:
	USword();

	virtual void OnItemInteract(UItemStack* InteractItemStack, AActor* Instigator, AActor* ItemActorEntity) override;
	virtual void OnWeaponUse() override;
	virtual void OnWeaponHit(UItemStack* WeaponHit, AActor* Instigator, AActor* ItemActorEntity) override;
	virtual void EndItemInteract() override;
};
