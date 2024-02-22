// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharmingCraft/Core/UI/ICommonUI.h"
#include "CharmingCraft/Core/UI/Handler/UserWidgetEventHandler.h"
#include "WidgetHolder.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UWidgetHolder : public UUserWidget, public ICommonUI
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UUserWidgetEventHandler> UserWidgetEventHandler;

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

	virtual bool RemoveWidget_Implementation() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
