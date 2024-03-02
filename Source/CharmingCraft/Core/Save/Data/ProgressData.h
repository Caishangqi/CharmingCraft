// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSaveGame.h"
#include "GameFramework/SaveGame.h"
#include "ProgressData.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UProgressData : public UBaseSaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "SaveData")
	FGuid UniqueID;
};
