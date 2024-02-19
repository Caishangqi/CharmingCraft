// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerModeWidget.generated.h"

enum class EPlayerMode : uint8;
class UPlayerModeManager;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerModeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UPlayerModeManager> PlayerModeManager;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnPlayerModeChangeEvent(ACharacter * Instigator, EPlayerMode ToMode);
};
