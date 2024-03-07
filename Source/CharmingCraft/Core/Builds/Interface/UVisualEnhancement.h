// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UVisualEnhancement.generated.h"

UINTERFACE(MinimalAPI)
/**
 * 
 */
class UVisualEnhancementInterface : public UInterface
{
	GENERATED_BODY()
};

class CHARMINGCRAFT_API IVisualEnhancementInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetObjectTranslucent(float Value);
};
