// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "UObject/Object.h"
#include "Templates/Function.h"
#include "WorldManager.generated.h"
class ULevelStreamingDynamic;

USTRUCT(BlueprintType)
struct FLevelStreamingDynamicResult
{
	GENERATED_BODY()

public:
	FLevelStreamingDynamicResult(): IsSuccess(false), LoadedWorld(nullptr)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULevelStreamingDynamic> LoadedWorld;
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
	// 委托事件，用于在关卡加载完毕后通知
	FOnLevelLoadedDelegate OnLevelLoaded;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, ULevelStreamingDynamic*> LoadedWorlds;


	UFUNCTION(BlueprintCallable)
	bool LoadGameLevel(FName LevelName);

	/*!
	 * Teleport player to specific warp (Target level point), please ensure you load or set loaded level
	 * visible before teleport, or it will not work
	 * @param PlayerCharacter The Character you want to teleport
	 * @param TargetLevel The target Level that include the warp
	 * @param WarpName The warp name
	 * @return whether or not teleport success
	 */
	UFUNCTION(BlueprintCallable)
	bool TeleportPlayerToWarp(APawn* PlayerCharacter, const TSoftObjectPtr<UWorld> TargetLevel, const FName WarpName);
	UFUNCTION(BlueprintCallable)
	bool TeleportPlayerToWarpLocal(APawn* PlayerCharacter, const FName WarpPoint);

	// 加载完成的回调函数
	UFUNCTION(BlueprintCallable)
	void OnLevelLoadedCallback();
	


	UFUNCTION(BlueprintCallable)
	FLevelStreamingDynamicResult LoadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel, bool UnloadRemainWorld = false);
	UFUNCTION(BlueprintCallable)
	bool UnloadAllWorldInstance(const TSoftObjectPtr<UWorld> WhiteListLevel = nullptr);
	UFUNCTION(BlueprintCallable)
	FLevelStreamingDynamicResult UnloadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel);
	UFUNCTION(BlueprintCallable)
	FLevelStreamingDynamicResult UnloadAndRemoveWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel);

	/*!
	 * 
	 * @param Instigator The instigator that unload the chunk
	 * @param TargetWorld The world that chunk belongs to
	 * @param TargetChunk The specific chunk you want to unload
	 * @return whether unload chunk success
	 */
	UFUNCTION(BlueprintCallable)
	bool UnloadWorldChunk(UObject* Instigator, UWorld* TargetWorld, ALandChunk* TargetChunk);

	// Interface
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
};
