// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScriptActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UScriptActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IScriptActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool AddRunningScriptObject(UNativeScriptObject* ScriptObject);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool RemoveRunningScriptObject(UNativeScriptObject* ScriptObject);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool SuspendRunningScriptObject(UNativeScriptObject* ScriptObject);
	
};
