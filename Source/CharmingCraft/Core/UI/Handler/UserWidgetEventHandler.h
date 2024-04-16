// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Core/Container/Inventory/InventoryComponent.h"
#include "UserWidgetEventHandler.generated.h"

class UWidgetHolder;
class UGameEventHandler;
class UCharmingCraftInstance;
class ADCharacter;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UUserWidgetEventHandler : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UCharmingCraftInstance> GameInstance;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UGameEventHandler> GamePlayLogicManager;

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TObjectPtr<UUserWidget>> LoadedUserWidget;

	/*!
	 * Close specific subclass of UWidgetHolder, the first one in
	 * LoadedUserWidget
	 * @param TargetWidgetHolder 
	 * @return true if remove sucess
	 */
	UFUNCTION(BlueprintCallable)
	bool CloseWidgetByClass(TSubclassOf<UWidgetHolder> TargetWidgetHolder);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerOpenInventoryEvent(ACharacter* Instigator, UObject* Creator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerOpenTravelMapEvent(ACharacter* Instigator, UObject* Creator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerOpenContainerEvent(ACharacter* Instigator, UInventoryComponent* TargetContainer, UObject* Creator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerClickMoveEvent(ACharacter* Instigator, FVector TargetLocation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnItemDetailDisplayEvent(UItemStack* ItemToDisplay, UObject* Creator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCloseWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnOpenWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);
};
