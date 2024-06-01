// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeDungeonHandler.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "Kismet/GameplayStatics.h"

UNativeDungeonHandler::UNativeDungeonHandler()
{
	UE_LOG(LogChamingCraftDungeon, Warning, TEXT("[💀]  初始化地牢处理器"));
}

bool UNativeDungeonHandler::AddInstanceToSet(ANativeBaseDungeonInstance* DungeonInstance)
{
	if (LoadedDungeonInstances.Contains(DungeonInstance))
	{
		return false;
	}
	else
	{
		LoadedDungeonInstances.Add(DungeonInstance);
	}

	return true;
}

UCharmingCraftInstance* UNativeDungeonHandler::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}
