// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UBreakable.generated.h"
UINTERFACE(MinimalAPI)
/**
 * 
 */
class UBreakableInterface : public UInterface
{
	GENERATED_BODY()
};

class CHARMINGCRAFT_API IBreakableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool OnBlockPlace(ACharacter* Instigator, AActor* BlockPlaced);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool OnBlockBreak(ACharacter* Instigator, AActor* BlockBreak);
};
