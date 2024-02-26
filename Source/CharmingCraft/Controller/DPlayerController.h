// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class ADPlayerAIController;
class UCharmingCraftInstance;
class UGameEventHandler;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADPlayerController();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCharmingCraftInstance> GameInstance;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UGameEventHandler> GamePlayLogicManager;

	virtual void BeginPlay() override;
};
