// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Object/Structs/Attribute/FHitData.h"
#include "ActionOnHitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UActionOnHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IActionOnHitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnActionHit(APawn* InstigatorPawn, FHitData HitData);
};
