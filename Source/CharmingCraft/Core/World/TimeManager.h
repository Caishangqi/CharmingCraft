// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "UObject/Object.h"
#include "TimeManager.generated.h"

/**
 * Time Strucutre for time system
 * it contains 4 Game time units
 * and support auto cast between
 * time units
 */
USTRUCT(BlueprintType)
struct FTimeData
{
	GENERATED_BODY()

	FTimeData() : Year(0), Day(0), Hour(0), Min(0)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Year;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Day;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Hour;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Min;

public:
	// Increment functions to handle time overflow
	void IncrementMinute(int32 AdditionalSeconds = 1)
	{
		Min += AdditionalSeconds;
		NormalizeTime();
	}

	void IncrementHour(int32 AdditionalHours = 1)
	{
		Hour += AdditionalHours;
		NormalizeTime();
	}

	void NormalizeTime()
	{
		if (Min >= 60)
		{
			Hour += Min / 60;
			Min %= 60;
		}

		if (Hour >= 24)
		{
			Day += Hour / 24;
			Hour %= 24;
		}

		// Assuming each year has 365 days for simplicity
		if (Day >= 365)
		{
			Year += Day / 365;
			Day %= 365;
		}
	}

	// Operator overloading for ++
	FTimeData& operator++()
	{
		IncrementMinute(1);
		return *this;
	}

	// Operator overloading for +=
	FTimeData& operator+=(int32 Seconds)
	{
		IncrementMinute(Seconds);
		return *this;
	}

	// Operator overloading for + (int32 seconds)
	friend FTimeData operator+(FTimeData lhs, int32 Minute)
	{
		lhs += Minute;
		return lhs;
	}

	// Operator overloading for + (FTimeData)
	friend FTimeData operator+(const FTimeData& lhs, const FTimeData& rhs)
	{
		FTimeData result;
		result.Min = lhs.Min + rhs.Min;
		result.Hour = lhs.Hour + rhs.Hour;
		result.Day = lhs.Day + rhs.Day;
		result.Year = lhs.Year + rhs.Year;
		result.NormalizeTime();
		return result;
	}
	
};

UCLASS()
class CHARMINGCRAFT_API UTimeManager : public UObject, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	// Global time, future support time zone for different map

	// Total tick time for a game day
	// Default 2 s = 1 min game Total 2880 tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TickTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimeData TimeData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle GlobalTimeHandler;

public:
	UTimeManager();

public:
	UFUNCTION(BlueprintCallable)
	void StartGlobalTimer();
	UFUNCTION(BlueprintCallable)
	void PauseGlobalTimer();
	UFUNCTION(BlueprintCallable)
	void UnpauseGlobalTimer();
	UFUNCTION(BlueprintCallable)
	void OnGlobalTimerTick();
	UFUNCTION(BlueprintCallable)
	FTimeData & GetTimeDataFromTickTime(int32 TickTimeData);
public:
	// Interface
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
};
