// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/Function.h"
#include "WorldManager.generated.h"

/**
 * 
 */
// 在游戏模式头文件中
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoadedDelegate);

UCLASS()
class CHARMINGCRAFT_API UWorldManager : public UObject
{
	GENERATED_BODY()

public:
	// 委托事件，用于在关卡加载完毕后通知
	FOnLevelLoadedDelegate OnLevelLoaded;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSoftObjectPtr<UWorld> CurrentLoadWorld;

	UFUNCTION(BlueprintCallable)
	bool LoadGameLevel(FName LevelName);
	
	UFUNCTION(BlueprintCallable)
	bool TeleportPlayerToWarp(APawn* PlayerCharacter, FName TargetWorldName, const FName WarpPoint);
	UFUNCTION(BlueprintCallable)
	bool TeleportPlayerToWarpLocal(APawn* PlayerCharacter, const FName WarpPoint);

	// 加载完成的回调函数
	UFUNCTION(BlueprintCallable)
	void OnLevelLoadedCallback();
	
	// Life Time
	/*!
	 * Unload Game level from specific world, it usually handle unload and pause chunk
	 * @param TargetWorld The Target Game World need to unload
	 * @param Callback The Callback function to execute after unload success
	 * @return whether unload success
	 */
	bool NativeUnloadGameLevel(UWorld* TargetWorld, TFunction<void(void)>&& Callback);

	/*!
	 * 
	 * @param Instigator The instigator that unload the chunk
	 * @param TargetWorld The world that chunk belongs to
	 * @param TargetChunk The specific chunk you want to unload
	 * @return whether unload chunk success
	 */
	UFUNCTION(BlueprintCallable)
	bool UnloadWorldChunk(UObject* Instigator, UWorld* TargetWorld, ALandChunk* TargetChunk);
	
};
