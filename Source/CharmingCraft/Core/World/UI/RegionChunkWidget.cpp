// Fill out your copyright notice in the Description page of Project Settings.


#include "RegionChunkWidget.h"

#include "Kismet/GameplayStatics.h"

FLevelStreamingDynamicResult URegionChunkWidget::TravelToTargetWorld(APawn* Instigator)
{
	FLevelStreamingDynamicResult Out;

	return Out;
}

bool URegionChunkWidget::CanPlayerTravelToRegion()
{
	if (TargetWorld.LoadSynchronous() == nullptr)
	{
		return false;
	}
	return true;
}

UCharmingCraftInstance* URegionChunkWidget::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UGameEventHandler* URegionChunkWidget::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}

UWorldManager* URegionChunkWidget::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
}
