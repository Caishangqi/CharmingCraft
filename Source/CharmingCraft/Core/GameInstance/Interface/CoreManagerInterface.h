// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/CharmingCraftInstance.h"
#include "UObject/Interface.h"
#include "CoreManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCoreManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API ICoreManagerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UCharmingCraftInstance* GetGameInstance();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UWorldManager* GetWorldManager();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UGameEventHandler* GetGameEventHandler();
};
