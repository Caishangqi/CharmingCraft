// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DGameplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
/*
 *	Interface的目的是有一些共有的API, 比如说游戏内的箱子可以被打开,你需要一个交互行为
 *	又或者是玩家死亡的尸体你希望其他玩家能够与其进行互动
 *
 *	在设置好Interface后其他组件或者实例可以基于实例不同类型来实现接口的方法
 */
class UDGameplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 上方的UDGameplayInterface 不应当添加任何东西, 功能性实现在下方 IDGameplayInterface
 * 中, 其中前缀 I 意为接口
 */
class CHARMINGCRAFT_API IDGameplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*!
	 *	@param InstigatorPawn 哪个Pawn激活的这个方法, 通常是玩家
	 */
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent) // UFUNCTION(BlueprintNativeEvent) 允许把这个函数暴露到蓝图中
	void Interact(APawn* InstigatorPawn); //Instigator = Initiator 谁激活的
};
