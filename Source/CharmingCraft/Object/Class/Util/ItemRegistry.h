// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "UObject/Object.h"
#include "ItemRegistry.generated.h"

class UItem;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UItemRegistry : public UObject
{
	GENERATED_BODY()

public:
	// 单例获取函数
	static UItemRegistry* Get();

	void InitializeRegistry();

	UPROPERTY()
	TMap<EMaterial, TSubclassOf<UItem>> ItemMap;

private:
	// 单例实例
	static UItemRegistry* Instance;
};
