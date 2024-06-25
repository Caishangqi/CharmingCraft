// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeEquipmentAction.h"
#include "NativeStandardRangedAction.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UNativeStandardRangedAction : public UNativeEquipmentAction
{
	GENERATED_BODY()
public:
	
	UNativeStandardRangedAction();
	
public:

	UFUNCTION(BlueprintCallable)
	FVector GetCastMouseLocation(APawn* Instigator);
	
	
	virtual void StartAction_Implementation(APawn* Instigator) override;
};
