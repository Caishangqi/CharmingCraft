// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharmingCraft/Core/UI/ICommonUI.h"
#include "CharmingCraft/Core/UI/Handler/UserWidgetEventHandler.h"
#include "WidgetHolder.generated.h"

/*!
 * @author Shangqi Cai
 * WidgetHolder is subclass of UUserWidget, mainly handle the max amount widget can
 * appear on the screen, WidgetHolder can be control by event in UserWidgetEventHandler
 * For example, if you want to player click move event destroy all WidgetHolder who's
 * creator is "craft-table" you can set Creator "craft-table" and bind new event on UserWidgetEventHandler
 */
UCLASS()
class CHARMINGCRAFT_API UWidgetHolder : public UUserWidget, public ICommonUI
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UUserWidgetEventHandler> UserWidgetEventHandler;
	/*
	 *	Creator tell UI system who create this Widget, in some case, the container invoke
	 *	Player's inventory is different from Player invoke PlayerOpen Event
	 *
	 *	更新说明，这里是逻辑处理属性，比如说玩家可以打开物品背包但是方法有很多种，有由Container
	 *	执行函数开启的也可以他们自己使用tab键开启的，这里记录逻辑上而言UI的创建者
	 */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UObject> Creator;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UCharmingCraftInstance> GameInstance;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 MaxInstanceOfWidget;

	/*!
	 * Get this widget handler, basically the outer who create it
	 * @return Return the Handler UUserWidgetEventHandler
	 */
	UFUNCTION(BlueprintCallable)
	UUserWidgetEventHandler* GetWidgetHolder();

	UFUNCTION(BlueprintCallable)
	UObject* GetCreator();

	/*!
	 * Handle Open Widget Event, the event broadcast when native construct
	 * use this event to listen widget open globally, for example, in player
	 * map widget you can listen to player inventory open event.
	 * @param Instigator Who open the event
	 * @param TargetWidget The target widget that was open
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnOpenWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);
	/*!
	 * Handle Close Widget Event, the event broadcase when native NativeDestruct
	 * called. 
	 * @param Instigator 
	 * @param TargetWidget 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCloseWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);

	virtual bool RemoveWidget_Implementation() override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
