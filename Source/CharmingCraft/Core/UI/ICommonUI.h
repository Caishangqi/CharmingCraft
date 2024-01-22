// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICommonUI.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCommonUI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API ICommonUI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HideEntireWidget();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DisplayEntireWidget();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	// Use for update information in widget manually,or use event broadcast trigger this function
	void UpdateWidgetContext();
};
