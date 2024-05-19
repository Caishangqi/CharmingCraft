// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TimeManager.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UTimeManager : public UObject
{
	GENERATED_BODY()

public:
	// Global time, future support time zone for different map

	// Default 2 s = 1 min game Total 2880 tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TickTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Day = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Hour = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Second = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle GlobalTimeHandler;

public:
	UTimeManager();

public:
	UFUNCTION(BlueprintCallable)
	void StartGlobalTimer();
};
