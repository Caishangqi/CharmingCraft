// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "Data/FSaveSlotInfo.h"
#include "UObject/Object.h"
#include "GamePlayLogicManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinDelegate, ACharacter*, PlayerCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerOpenInventoryDelegate, ACharacter*, PlayerCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLeaveDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerSaveDelegate);

// TODO: 尝试玩家加入世界后，播报事件，让组件接收到这个事件后由组件内部进行调用
UCLASS()
class CHARMINGCRAFT_API UGamePlayLogicManager : public UObject
{
	GENERATED_BODY()

	UGamePlayLogicManager();

public:
	// Global Variable


	FOnPlayerJoinDelegate OnPlayerJoin;
	FOnPlayerLeaveDelegate OnPlayerLeave;
	FOnPlayerSaveDelegate OnPlayerSave;

	FOnPlayerOpenInventoryDelegate OnPlayerOpenInventory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADCharacter> BlueprintCharacterClassReference;

	UFUNCTION(BlueprintCallable)
	void OnPlayerJoinEvent();
	UFUNCTION(BlueprintCallable)
	void OnPlayerLeaveEvent();
	UFUNCTION(BlueprintCallable)
	void OnPlayerOpenInventoryEvent(ACharacter* Instigator);
};
