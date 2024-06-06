// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeCraftWorld.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Libarary/CoreComponents.h"
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
	// Bind Event
	UCoreComponents::GetGameEventHandler(this)->OnPlayerJoinWorld.AddDynamic(
		this, &UNativeCraftWorld::OnPlayerJoinWorld);

	bool IsSuccessLoadWorldInstance;
	GamePlayWorldInstance = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
		this->GetOuter(), WorldMap, FVector(0, 0, 0), FRotator(0, 0, 0), IsSuccessLoadWorldInstance);
	GamePlayWorldInstance->bInitiallyVisible = false;
	//GamePlayWorldInstance->SetShouldBeVisible(false);
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

TArray<ACraftWorldWarpPoint*> UNativeCraftWorld::GetLoadedWarpPoints()
{
	return LoadedWarpPoints;
}

ULevelStreamingDynamic* UNativeCraftWorld::GetGamePlayWorldInstance()
{
	return GamePlayWorldInstance;
}

/*
bool UNativeCraftWorld::CheckCraftWorldStatus()
{
	GetWorld()->GetTimerManager().SetTimer(
		CraftWorldCheckHandle,
		this,
		&UNativeCraftWorld::BroadcastCraftWorldStatus_Internal,
		0.1f,
		true // 重复执行
	);
	return true;
}

void UNativeCraftWorld::BroadcastCraftWorldStatus_Internal()
{
	if (GamePlayWorldInstance->GetLevelScriptActor())
	{
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[❕] LevelScripActor is BeginningPlay"
		       ));
		OnCraftWorldPrepare.Broadcast();
		GetWorld()->GetTimerManager().PauseTimer(CraftWorldCheckHandle);
	}
}
*/

void UNativeCraftWorld::OnPlayerJoinWorld_Implementation(ACharacter* Instigator, UNativeCraftWorld* TargetWorld)
{
	if (TargetWorld == this)
	{
		PlayerList.Add(Instigator);
	}
	else
	{
		PlayerList.Remove(Instigator);
	}
}
