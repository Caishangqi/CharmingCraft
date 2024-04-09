// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "CharmingCraft/Core/Builds/LevelWarpPoint.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Resource/Chunk/LandChunk.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"

bool UWorldManager::LoadGameLevel(FName LevelName)

{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OnLevelLoadedCallback";
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	if (UGameplayStatics::GetCurrentLevelName(this, true) == "PersistentLevel")
	{
		// 异步加载关卡
		UGameplayStatics::LoadStreamLevel(this, LevelName, true, true, LatentInfo);
		return false;
	}
	UGameplayStatics::OpenLevel(this, FName("L_PersistentLevel"));
	// 异步加载关卡
	UGameplayStatics::LoadStreamLevel(this, LevelName, true, true, LatentInfo);
	return true;
}

bool UWorldManager::TeleportPlayerToWarp(APawn* PlayerCharacter, FName TargetWorldName, const FName WarpPoint)
{
	const FString LevelPath = TargetWorldName.ToString();

	if (PlayerCharacter && TargetWorldName.IsNone())
	{
		TeleportPlayerToWarpLocal(PlayerCharacter, WarpPoint);
	}

	if (PlayerCharacter->GetWorld()->GetName() != LevelPath)
	{
		bool success;

		TSoftObjectPtr<ULevelStreamingDynamic> PendingAddedWorld = ULevelStreamingDynamic::LoadLevelInstance(
			this, TargetWorldName.ToString(), FVector(0, 0, 0), FRotator(0, 0, 0),
			success);
		if (success)
		{
			//LoadedWorlds.Add(TargetWorldName, PendingAddedWorld.Get());
			//PendingAddedWorld->OnLevelLoaded.AddDynamic(this, OnLevelLoadedCallback);
		}
		TeleportPlayerToWarpLocal(PlayerCharacter, WarpPoint);
	}
	return false;
}

bool UWorldManager::TeleportPlayerToWarpLocal(APawn* PlayerCharacter, const FName WarpPoint)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ALevelWarpPoint::StaticClass(), OutActors);
	for (const auto OutActor : OutActors)
	{
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[🌍]  Find Warp %s in world %s"), *Cast<ALevelWarpPoint>(OutActor)->TargetName,
		       *PlayerCharacter->GetWorld()->GetName());
		if (Cast<ALevelWarpPoint>(OutActor)->TargetName == WarpPoint)
		{
			PlayerCharacter->TeleportTo(OutActor->GetActorLocation(), FRotator());
			UE_LOG(LogChamingCraftWorld, Warning,
			       TEXT("[🌍]  Teleport Player to target Warp: %s"), *WarpPoint.ToString());
			return true;
		}
	}
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Target warp does not exist, use the default spawn, please check the warp name"));
	return false;
}

void UWorldManager::OnLevelLoadedCallback()
{
	OnLevelLoaded.Broadcast();
}

bool UWorldManager::NativeUnloadGameLevel(UWorld* TargetWorld, TFunction<void()>&& Callback)
{
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Unloading World Chunks...\n"
		       "		Target World: %s"), *TargetWorld->GetName());
	GetGameEventHandler()->OnUnloadGameLevelEvent(TargetWorld);
	// Find All Loaded Chunk in this world and prepare unload the chunk
	TArray<AActor*> OutChunks;
	UGameplayStatics::GetAllActorsOfClass(this, ALandChunk::StaticClass(), OutChunks);
	for (const auto OutChunk : OutChunks)
	{
		//Cast<ALandChunk>(OutChunk)->UnloadWorldChunk(this,MoveTemp(Callback));
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[🌍]  Unloading World Last Chunk\n"
			       "		Target World: %s\n"
			       "		Target Chunk: %s"), *TargetWorld->GetName(), *OutChunk->GetName());
		UnloadWorldChunk(this, TargetWorld, Cast<ALandChunk>(OutChunk));
		Callback();
	}


	return true;
}

bool UWorldManager::LoadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel)
{
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetMapName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel->GetMapName()];
		LevelStreamingDynamic->SetShouldBeVisible(true);
		return true;
	}
	bool IsSuccess;
	ULevelStreamingDynamic* LevelStreamingDynamic = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
		this, TargetLevel, FVector(0, 0, 0), FRotator(0, 0, 0), IsSuccess);
	if (LevelStreamingDynamic != nullptr)
	{
		LevelStreamingDynamic->OnLevelLoaded.AddDynamic(this, &UWorldManager::OnLevelLoadedCallback);
	}
	if (IsSuccess)
	{
		LoadedWorlds.Add(TargetLevel->GetMapName(), LevelStreamingDynamic);
		return true;
	}
	return false;
}

bool UWorldManager::UnloadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel)
{
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetMapName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel->GetMapName()];
		LevelStreamingDynamic->SetShouldBeVisible(false);
		return true;
	}
	return false;
}

bool UWorldManager::UnloadAndRemoveWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel)
{
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetMapName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel->GetMapName()];
		LevelStreamingDynamic->SetShouldBeVisible(false);
		LevelStreamingDynamic->SetShouldBeLoaded(false);
		return true;
	}
	return false;
}

bool UWorldManager::UnloadWorldChunk(UObject* Instigator, UWorld* TargetWorld, ALandChunk* TargetChunk)
{
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Unloading Chunks form world\n"
		       "		Target World: %s\n"
		       "		Target Chunk: %s"), *TargetWorld->GetName(), *TargetChunk->GetName());
	GetGameEventHandler()->OnUnloadWorldChunkEvent(Instigator, TargetWorld, TargetChunk);
	return true; // 12
}

UCharmingCraftInstance* UWorldManager::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(GetOuter());
}

UGameEventHandler* UWorldManager::GetGameEventHandler_Implementation()
{
	return GetGameInstance()->GetGameEventHandler();
}
