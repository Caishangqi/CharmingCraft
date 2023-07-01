// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DProjectileBase.h"
#include "DDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADDashProjectile : public ADProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category= "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category= "Teleport")
	float DetonateDelay;

	// Handle to cancel timer if we already hit something
	FTimerHandle TimerHandle_DelayedDetonate;

	// Base class using BlueprintNativeEvent, we must override the Implementation not the Explode()
	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void BeginPlay() override;

public:
	ADDashProjectile();
};
