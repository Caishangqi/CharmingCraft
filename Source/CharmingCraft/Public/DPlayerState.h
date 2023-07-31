// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DPlayerState.generated.h"

/*
 * 定义一个三个参数的多播委托，将其命名为FOnCreditsChanged类型。
 * 当调用这个委托时，执行注册在委托里的所有函数
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ADPlayerState*, PlayerState, int32, NewCredits, int32,
                                               Delta);

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category= "Credits")
	int32 Credits;

public:
	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 GetCredits() const;

	UFUNCTION(BlueprintCallable, Category = "Credits")
	bool AddCredit(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Credits")
	bool RemoveCredit(int32 Delta);

	/* BlueprintAssignable 只能与多播委托共用。可以在蓝图中指定函数 */
	UPROPERTY(BlueprintAssignable, Category= "Events")
	FOnCreditsChanged OnCreditsChanged;
};
