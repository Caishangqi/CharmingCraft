// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPlayerInfo.h"
#include "GameFramework/SaveGame.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerData : public USaveGame
{
	GENERATED_BODY()

public:
	// Player Basic Info, typically decided when player creation
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = "PlayerInformation")
	FPlayerInfo PlayerInfo;
};
