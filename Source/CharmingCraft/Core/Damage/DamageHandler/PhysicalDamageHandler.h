// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageHandler.h"
#include "PhysicalDamageHandler.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CHARMINGCRAFT_API UPhysicalDamageHandler : public UDamageHandler
{
	GENERATED_BODY()

public:
	virtual void HandleDamage(FHitData HitData) override;
	virtual void ApplyDataToAttribute(APawn* InstigatorPawn, float Data) override;
};
