// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class ADPlayerAIController;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Controller")
	ADPlayerAIController* PlayerAIController;

	ADPlayerController();
};
