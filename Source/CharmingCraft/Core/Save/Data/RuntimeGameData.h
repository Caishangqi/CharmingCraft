// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
};
