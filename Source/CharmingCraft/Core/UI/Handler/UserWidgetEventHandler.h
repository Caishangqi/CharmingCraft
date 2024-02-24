// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "Blueprint/UserWidget.h"
#include "CharmingCraft/Object/Components/DInventoryComponent.h"
#include "UserWidgetEventHandler.generated.h"

class UGamePlayLogicManager;
class UCharmingCraftInstance;
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
	TObjectPtr<UGamePlayLogicManager> GamePlayLogicManager;

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TObjectPtr<UUserWidget>> LoadedUserWidget;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerOpenInventoryEvent(ACharacter* Instigator, UObject* Creator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerOpenContainerEvent(ACharacter* Instigator, UDInventoryComponent* TargetContainer, UObject* Creator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerClickMoveEvent(ACharacter* Instigator, FVector TargetLocation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnItemDetailDisplayEvent(UItemStack* ItemToDisplay, UObject* Creator);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCloseWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);
	
};
