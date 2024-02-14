// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "Data/FSaveSlotInfo.h"
#include "UObject/Object.h"
#include "GamePlayLogicManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerJoinDelegate);

UCLASS()
class CHARMINGCRAFT_API UGamePlayLogicManager : public UObject
{
	GENERATED_BODY()

	UGamePlayLogicManager();

public:

	// Global Variable
	

	FOnPlayerJoinDelegate OnPlayerJoin;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADCharacter> BlueprintCharacterClassReference;

	UFUNCTION(BlueprintCallable)
	void OnPlayerJoinCallback();
	UFUNCTION(BlueprintCallable)
	void OnPlayerJoinBegin();
};
