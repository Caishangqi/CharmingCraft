// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
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

	UFUNCTION(BlueprintCallable)
	bool LoadGameLevel(FName LevelName);
	// 加载完成的回调函数
	UFUNCTION(BlueprintCallable)
	void OnLevelLoadedCallback();
};
