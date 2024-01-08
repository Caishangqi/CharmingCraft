// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "UObject/Object.h"
#include "DamageHandler.generated.h"

class UDAttributeComponent;
/**
 * 
 */
UCLASS(BlueprintType)
class CHARMINGCRAFT_API UDamageHandler : public UObject
{
	GENERATED_BODY()

protected:
	TObjectPtr<UDamageHandler> NextHandler;

public:
	UFUNCTION(BlueprintCallable)
	virtual void HandleDamage(FHitData HitData);
	virtual void SetNextHandler(UDamageHandler* NewNextHandler);
	virtual UDAttributeComponent* GetOuterAttributeComponent();
	
	virtual void ApplyDataToAttribute(float Data);
};
