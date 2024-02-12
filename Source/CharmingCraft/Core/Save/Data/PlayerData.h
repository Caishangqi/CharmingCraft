// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSaveGame.h"
#include "FPlayerInfo.h"
#include "FPlayerLocation.h"
#include "GameFramework/SaveGame.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerData : public UBaseSaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "SaveData")
	FGuid UniqueID;

	// Player Basic Info, typically decided when player creation
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerInformation")
	FPlayerInfo PlayerInfo;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerInformation")
	FPlayerLocation PlayerLocation;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerInformation")
	TArray<FString> PlayerInventoryItems;

	// RunTimePlayer Information
	// UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RunTimePlayer Information")
	// TObjectPtr<APawn> PlayerCharacter;

	virtual void PerformInGameDataSave() override;
};
