// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OccludeObject.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UOccludeObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IOccludeObject
{
	GENERATED_BODY()

public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool HideOccludedComponent();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool ShowOccludedComponent();

public:
};
