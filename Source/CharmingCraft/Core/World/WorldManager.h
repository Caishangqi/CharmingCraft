// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "UObject/Object.h"
#include "Templates/Function.h"
#include "WorldManager.generated.h"

class UNativeCraftWorld;
class AWorldEntityManager;
class ULevelStreamingDynamic;

USTRUCT(BlueprintType)
struct FCharmingCraftWorld
{
	GENERATED_BODY()

public:
	FCharmingCraftWorld(): IsSuccess(false), GamePlayWorld(nullptr)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> WorldTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULevelStreamingDynamic> GamePlayWorld;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACharacter>> PlayerList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WorldName;
};

/**
 * 
 */
// 在游戏模式头文件中
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoadedDelegate);

UCLASS()
class CHARMINGCRAFT_API UWorldManager : public UObject, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	UE_DEPRECATED(5.3, "The WorldManager has been refactory, please use new API")
	// 委托事件，用于在关卡加载完毕后通知
	FOnLevelLoadedDelegate OnLevelLoaded;

	UE_DEPRECATED(5.3, "The WorldManager has been refactory, please use new API")
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, ULevelStreamingDynamic*> LoadedWorlds;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TObjectPtr<UNativeCraftWorld>> Worlds;

	/*!
	 * Return playerr current level, this is different from GetWorld()
	 * double check with LoadedWorlds and game runtime data
	 * @param PlayerCharacter 
	 * @return FLevelStreamingDynamicResult
	 */
	UE_DEPRECATED(5.3, "The WorldManager has been refactory, please use new API")
	UFUNCTION(BlueprintCallable)
	FCharmingCraftWorld GetPlayerCurrentLevel(ACharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* GetPlayerCurrentWorld(ACharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* GetWorldByWorldName(FString SearchWorldName);

	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* LoadCraftWorldInMemory(TSubclassOf<UNativeCraftWorld> TargetWorld);
	// Get the CraftWorld that currently display to player
	// Note: Only 1 World could display !
	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* GetShownWorld();

	UFUNCTION(BlueprintCallable)
	bool UnLoadCraftWorldInMemory(UNativeCraftWorld* TargetWorld);

	/*!
	 * Shown CraftWorld to player, the function will automatically Hidden
	 * all CraftWorld that is not {TargetWorld}
	 * @param TargetWorld The target CraftWorld need to be shown to player
	 * @return TargetWorld
	 */
	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* ShownCraftWorld(UNativeCraftWorld* TargetWorld);

	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* HiddenCraftWorld(UNativeCraftWorld* TargetWorld);

	UNativeCraftWorld* TeleportPlayerToWorld_Internal(ACharacter* PlayerCharacter, FString WorldName,
	                                                  UNativeCraftWorld* TargetWorld = nullptr);

	UFUNCTION(BlueprintCallable)
	bool TeleportPlayerToWarp(APawn* PlayerCharacter, const FName WarpPoint);

	/*!
	 * This is a more official or logic way to bind runtime generated actor to a
	 * specific level instance, be sure you put a WorldEntityManager in your world
	 * or else it will return null pointer
	 *
	 * Also be sure to load only ONE WorldEntityManager in the world or it will cause
	 * problem
	 *
	 * Alternatively if you don't want to put AWorldEntityManager in the level manually
	 * you can use GetPlayerCurrentLevel and get level instance related script actor
	 * although it is wierd @see GetPlayerCurrentLevel()
	 * @return AWorldEntityManager related to current level
	 */
	UFUNCTION(BlueprintCallable)
	AWorldEntityManager* GetWorldEntityManager();

	UE_DEPRECATED(5.3, "The WorldManager has been refactory, please use new API")
	UFUNCTION(BlueprintCallable)
	bool LoadGameLevel(FName LevelName);

	/*!
	 * Teleport player to specific Warp of ACraftWorldWarpPoint
	 * please check the level is loaded and visible before teleport
	 * @param PlayerCharacter 
	 * @param WarpPoint 
	 * @return whether or not teleport successful
	 */
	UFUNCTION(BlueprintCallable)
	bool TravelPlayerToWarp(APawn* PlayerCharacter, const FName WarpPoint);

	// 加载完成的回调函数
	UFUNCTION(BlueprintCallable)
	void OnLevelLoadedCallback();
	/*!
	 * Travel player to another world, this method is different from
	 * warp, warp generally used in scene change, for example, player
	 * enter a room. please ensure you load or set loaded level,
	 * visible before teleport, or it will not work
	 * @param PlayerCharacter
	 * @param TargetLevel 
	 * @return FLevelStreamingDynamicResult
	 */
	UFUNCTION(BlueprintCallable)
	FCharmingCraftWorld TravelPlayerToWorld(APawn* PlayerCharacter, const TSoftObjectPtr<UWorld> TargetLevel);

	/*!
	 * Travel player to another scene, use in scene travel of building,
	 * it will save the scene information in GameRuntime Data, and the
	 * data will retrived by GetPlayerCurrentLevel
	 *
	 * @see GetPlayerCurrentLevel()
	 *
	 * @param PlayerCharacter 
	 * @param TargetScene 
	 * @param WarpPoint 
	 * @param ResetSceneData If reset the scene data, it will clear the GameRuntime Data and
	 * set the PlayerSceneLocation to null after teleport player to warp point
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	FCharmingCraftWorld TravelPlayerToScene(APawn* PlayerCharacter, const TSoftObjectPtr<UWorld> TargetScene,
	                                        FName WarpPoint, bool ResetSceneData = true);


	UFUNCTION(BlueprintCallable)
	FCharmingCraftWorld LoadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel,
	                                      bool UnloadRemainWorld = false);
	UFUNCTION(BlueprintCallable)
	bool UnloadAllWorldInstance(const TSoftObjectPtr<UWorld> WhiteListLevel = nullptr);
	UFUNCTION(BlueprintCallable)
	FCharmingCraftWorld UnloadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel);
	UFUNCTION(BlueprintCallable)
	FCharmingCraftWorld UnloadAndRemoveWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel);

	/*!
	 * Check whether target world is loaded and visible
	 * @param TargetLevel Target Level you want to check
	 * @return 
	 */
	UFUNCTION(BlueprintCallable)
	bool GetWorldIsVisible(const TSoftObjectPtr<UWorld> TargetLevel);


	/*!
	 * @param Instigator The instigator that unload the chunk
	 * @param TargetChunk The specific chunk you want to unload
	 * @return whether unload chunk success
	 */
	UFUNCTION(BlueprintCallable)
	bool UnloadWorldChunk(UObject* Instigator, ALandChunk* TargetChunk);

public:
	// Interface
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
};
