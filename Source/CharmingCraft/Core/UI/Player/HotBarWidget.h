// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharmingCraft/Core/GameMode/PlayerMode/EPlayerMode.h"
#include "CharmingCraft/Core/UI/ICommonUI.h"
#include "HotBarWidget.generated.h"

class UCharmingCraftInstance;
class UPlayerModeManager;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UHotBarWidget : public UUserWidget, public ICommonUI
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UPlayerModeManager> PlayerModeManager;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UCharmingCraftInstance> GameInstance;

	virtual void NativeConstruct() override;


public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DisplayHotBarByGameMode(ACharacter* Character, EPlayerMode TargetMode);
};
