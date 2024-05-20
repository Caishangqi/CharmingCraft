// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"


UTimeManager::UTimeManager(): TickTime(0)
{
}

void UTimeManager::StartGlobalTimer()
{
	GetGameInstance_Implementation()->GetTimerManager().SetTimer(GlobalTimeHandler, this,
	                                                             &UTimeManager::OnGlobalTimerTick, 2.0f, true);
}

void UTimeManager::PauseGlobalTimer()
{
	if (GlobalTimeHandler.IsValid())
	{
		GetGameInstance_Implementation()->GetTimerManager().PauseTimer(GlobalTimeHandler);
	}
}

void UTimeManager::UnpauseGlobalTimer()
{
	if (GlobalTimeHandler.IsValid())
	{
		GetGameInstance_Implementation()->GetTimerManager().UnPauseTimer(GlobalTimeHandler);
	}
}


void UTimeManager::OnGlobalTimerTick()
{
	TickTime++;
	if (TickTime <= 2880)
	{
		TimeData += 1;
	}
	else
	{
		TickTime = 0;
	}
}

FTimeData& UTimeManager::GetTimeDataFromTickTime(int32 TickTimeData)
{
	FTimeData TimeData;
	
	return TimeData;
}

UCharmingCraftInstance* UTimeManager::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(GetOuter());
}

UGameEventHandler* UTimeManager::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}
