// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeRegionChunkWidget.h"

#include "Kismet/GameplayStatics.h"

FCharmingCraftWorld UNativeRegionChunkWidget::TravelToTargetWorld(APawn* Instigator)
{
	FCharmingCraftWorld Out;

	return Out;
}

bool UNativeRegionChunkWidget::CanPlayerTravelToRegion()
{
	if (TargetWorld.LoadSynchronous() == nullptr)
	{
		return false;
	}
	return true;
}

UCharmingCraftInstance* UNativeRegionChunkWidget::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UGameEventHandler* UNativeRegionChunkWidget::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}

UWorldManager* UNativeRegionChunkWidget::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
}
