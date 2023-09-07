﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemPreviewRender.generated.h"

class UItemStack;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UItemPreviewRender : public UObject
{
	GENERATED_BODY()

public:
	// 单例获取函数
	static UItemPreviewRender* Get();

	// 单例实例
	static UItemPreviewRender* Instance;

	void RenderItem(UItemStack* InputStack);
};
