// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CraftWorldStaticLibarary.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "CraftWorldStaticLibarary"))
class CHARMINGCRAFT_API UCraftWorldStaticLibarary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UWorldManager* GetWorldHandler(UObject* WorldContextObject)
	{
		return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(WorldContextObject))->GetWorldManager();
	}

	/*!
	 * Teleport Player to sepecific CraftWorld Instance, if the instance have set the "Spawn" Warp
	 * It will automatically receive event callback and teleport player
	 * @param PlayerCharacter Player you want to teleport
	 * @param WorldName The world Name usually set to null
	 * @param TargetWorld The CraftWorld instance of the teleport target
	 * @return CraftWorld instance
	 */
	UFUNCTION(BlueprintCallable)
	static UNativeCraftWorld* TeleportPlayerToWorld(ACharacter* PlayerCharacter, FString WorldName,
	                                                UNativeCraftWorld* TargetWorld = nullptr);
};
