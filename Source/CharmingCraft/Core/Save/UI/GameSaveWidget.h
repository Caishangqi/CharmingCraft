// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "GameSaveWidget.generated.h"

/**
 * 
 */
class UGameSaveManager;

UCLASS()
class CHARMINGCRAFT_API UGameSaveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGameSaveManager> SaveManager;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UWorldManager> WorldManager;

	virtual void NativePreConstruct() override;
};
