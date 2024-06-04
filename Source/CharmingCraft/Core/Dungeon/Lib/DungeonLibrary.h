// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Dungeon/NativeDungeonHandler.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameFramework/Character.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "DungeonLibrary"))
class CHARMINGCRAFT_API UDungeonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UNativeDungeonHandler* GetDungeonHandler(UObject* WorldContextObject)
	{
		return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(WorldContextObject))->GetDungeonHandler();
	}

	/*!
	 * Create Dungeon instance based on template class adding instance to dungeon
	 * handler and return dungeon instance.
	 * @param DungeonInstanceClass The Template class for creating dungeon instance
	 * @param Instigator The Context object that responsible for creating instance
	 * @return The dungeon instance
	 */
	UFUNCTION(BlueprintCallable)
	static ANativeBaseDungeonInstance* CreateDungeonInstance(
		TSubclassOf<ANativeBaseDungeonInstance> DungeonInstanceClass,
		UObject* Instigator)
	{
		UNativeDungeonHandler* DungeonHandler = GetDungeonHandler(Instigator);
		TObjectPtr<ANativeBaseDungeonInstance> NativeBaseDungeonInstance;
		FTransform DefaultTransform;
		NativeBaseDungeonInstance = Cast<ANativeBaseDungeonInstance>(
			UGameplayStatics::BeginDeferredActorSpawnFromClass(DungeonHandler, DungeonInstanceClass, DefaultTransform,
			                                                   ESpawnActorCollisionHandlingMethod::Undefined));
		DungeonHandler->AddInstanceToSet(NativeBaseDungeonInstance);
		UGameplayStatics::FinishSpawningActor(NativeBaseDungeonInstance, DefaultTransform);
		return NativeBaseDungeonInstance;
	}

	UFUNCTION(BlueprintCallable)
	static FCharmingCraftWorld TeleportPlayerToDungeonWorld(ACharacter* TargetPlayer, FCharmingCraftWorld TargetWorld,
	                                                        const FName WarpPoint = "Spawn")
	{
		TargetWorld.GamePlayWorld->SetShouldBeVisible(true);
		GetDungeonHandler(TargetPlayer)->GetWorldManager_Implementation()->
		                                 TeleportPlayerToWarp(TargetPlayer, WarpPoint);
		return TargetWorld;
	}
};
