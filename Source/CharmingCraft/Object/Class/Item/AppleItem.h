// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AppleItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UAppleItem : public UItem
{
	GENERATED_BODY()

public:
	UAppleItem();
	// 示例：苹果可能有一个特定的方法，使玩家恢复健康
	UFUNCTION(BlueprintCallable, Category="Apple")
	static void ConsumeForHealth();
};
