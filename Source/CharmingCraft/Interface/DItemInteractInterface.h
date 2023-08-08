// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DItemInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDItemInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IDItemInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent) // UFUNCTION(BlueprintNativeEvent) 允许把这个函数暴露到蓝图中
	void Interact(APawn* InstigatorPawn);
};
