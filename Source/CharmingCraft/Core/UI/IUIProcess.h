// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "IUIProcess.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUIProcess : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IUIProcess
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleDamageIndicator(FHitData HitData);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleHealthIndicator();
};
