// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSaveGame.h"
#include "GameFramework/SaveGame.h"
#include "LevelData.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ULevelData : public UBaseSaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "SaveData")
	FGuid UniqueID;
};
