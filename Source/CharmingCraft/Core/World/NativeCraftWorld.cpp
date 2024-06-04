// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeCraftWorld.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "Engine/LevelStreamingDynamic.h"

UNativeCraftWorld::UNativeCraftWorld(): IsLoadInMemory(false), IsVisible(false)
{
}

bool UNativeCraftWorld::InitializeWorldInstance()
{
	UE_LOG(LogChamingCraftWorld, Display,
	       TEXT("[🌍] Initialize World Instance\n"
		       "		World Name: %s"), *WorldName);
	bool IsSuccessLoadWorldInstance;
	GamePlayWorldInstance = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
		this->GetOuter(), WorldMap, FVector(0, 0, 0), FRotator(0, 0, 0), IsSuccessLoadWorldInstance);
	OnLevelHidden = GamePlayWorldInstance->OnLevelHidden;
	OnLevelLoaded = GamePlayWorldInstance->OnLevelLoaded;
	OnLevelShown = GamePlayWorldInstance->OnLevelShown;
	OnLevelUnloaded = GamePlayWorldInstance->OnLevelUnloaded;
	GamePlayWorldInstance->SetShouldBeVisible(false);
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("		States: %hhd"), IsSuccess);
	return IsSuccessLoadWorldInstance;
}

FString UNativeCraftWorld::GetCraftWorldName()
{
	return WorldName;
}

TArray<ACharacter*> UNativeCraftWorld::GetCraftWorldPlayers()
{
	return PlayerList;
}

TSoftObjectPtr<UWorld> UNativeCraftWorld::GetCraftWorldMapRes()
{
	return WorldMap;
}

ULevelStreamingDynamic* UNativeCraftWorld::GetGamePlayWorldInstance()
{
	return GamePlayWorldInstance;
}
