// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/CharmingCraftInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreComponents.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "CharmingCraft Core Component Library"))
class CHARMINGCRAFT_API UCoreComponents : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UCharmingCraftInstance* GetGameInstance(UObject* Context);

	UFUNCTION(BlueprintCallable)
	static UWorldManager * GetWorldManager(UObject* Context);
	
	UFUNCTION(BlueprintCallable)
	static UGameEventHandler * GetGameEventHandler(UObject* Context);

};
