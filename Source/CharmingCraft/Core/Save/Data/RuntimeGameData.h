// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSaveSlotInfo.h"
#include "UObject/Object.h"
#include "RuntimeGameData.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API URuntimeGameData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RunTimePlayer Information")
	TObjectPtr<ACharacter> PlayerCharacter;
	// The Runtime Save Data, when load a SaveSlot, first read save slot from save manager
	// then set the RuntimeSave and deserilize the runtime data in FSaveSlotInfo;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "RunTime Save Slot")
	FSaveSlotInfo RuntimeSave;

public:
	URuntimeGameData();
};
