// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "../Core/Save/Data/FSaveSlotInfo.h"
#include "UObject/Object.h"
#include "GameEventHandler.generated.h"

/**
 * Event Bus
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinDelegate, ACharacter*, PlayerCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerOpenInventoryDelegate, ACharacter*, PlayerCharacter, UObject *,
                                             Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerOpenContainerDelegate, ACharacter*, Instigator,
                                               UInventoryComponent*, TargetInventory, UObject *, Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerClickMoveDelegate, ACharacter*, Instigator,
                                             FVector, TargetLocation);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDetailDisplayDelegate, UItemStack*, ItemToDisplay,
                                             UObject *, Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCloseWidgetDelegate, UObject*, Instigator,
                                             UUserWidget *, TargetWidget);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLeaveDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerSaveDelegate);

// TODO: 尝试玩家加入世界后，播报事件，让组件接收到这个事件后由组件内部进行调用
UCLASS(BlueprintType)
class CHARMINGCRAFT_API UGameEventHandler : public UObject
{
	GENERATED_BODY()

	UGameEventHandler();

public:
	// Global Variable

	// Lowest
	FOnPlayerJoinDelegate OnPlayerJoin;
	FOnPlayerLeaveDelegate OnPlayerLeave;
	FOnPlayerSaveDelegate OnPlayerSave;
	// InGame
	FOnPlayerOpenInventoryDelegate OnPlayerOpenInventory;
	FOnCloseWidgetDelegate OnCloseWidget;
	FOnPlayerOpenContainerDelegate OnPlayerOpenContainer;
	FOnPlayerClickMoveDelegate OnPlayerClickMove;

	FOnItemDetailDisplayDelegate OnItemDetailDisplay;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADCharacter> BlueprintCharacterClassReference;

	UFUNCTION(BlueprintCallable)
	void OnPlayerJoinEvent();
	UFUNCTION(BlueprintCallable)
	void OnPlayerLeaveEvent();
	UFUNCTION(BlueprintCallable)
	void OnPlayerOpenInventoryEvent(ACharacter* Instigator, UObject* Creator);
	UFUNCTION(BlueprintCallable)
	void OnPlayerOpenContainerEvent(ACharacter* Instigator, UInventoryComponent* TargetContainer, UObject* Creator);
	UFUNCTION(BlueprintCallable)
	void OnPlayerClickMoveEvent(ACharacter* Instigator, FVector TargetLocation);

	UFUNCTION(BlueprintCallable)
	void OnItemDetailDisplayEvent(UItemStack* ItemToDisplay, UObject* Creator);
	UFUNCTION(BlueprintCallable)
	void OnCloseWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);
};
