// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "NativeCraftWorld.h"
#include "WorldEntityManager.h"
#include "CharmingCraft/Core/Builds/CraftWorldWarpPoint.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Camera/CameraManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Resource/Chunk/LandChunk.h"
#include "CharmingCraft/Core/Save/Data/RuntimeGameData.h"
#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"

UNativeCraftWorld* UWorldManager::GetPlayerCurrentWorld(ACharacter* PlayerCharacter)
{
	TObjectPtr<UPlayerData> PlayerData = UCoreComponents::GetGameInstance(PlayerCharacter)->GetRuntimeGameData()->
		RuntimeSave.PlayerData;

	UNativeCraftWorld* CraftWorld = PlayerData->PlayerLocation.GameWorld;
	bool IsWorldContainCurrentPlayer = CraftWorld->GetCraftWorldPlayers().Contains(PlayerCharacter);
	if (!IsWorldContainCurrentPlayer)
	{
		UE_LOG(LogChamingCraftWorld, Error,
		       TEXT("[🌍]  玩家不在任何世界中!\n"
			       "		(❌) 查找是否在加载世界时将玩家添加到 PlayerList 中"));
	}
	return CraftWorld;
}

UNativeCraftWorld* UWorldManager::GetPlayerCurrentRegion(ACharacter* PlayerCharacter)
{
	TObjectPtr<UPlayerData> PlayerData = UCoreComponents::GetGameInstance(PlayerCharacter)->GetRuntimeGameData()->
		RuntimeSave.PlayerData;
	UNativeCraftWorld* CraftWorld = PlayerData->PlayerLocation.RegionGameWorld;
	return CraftWorld;
}

UNativeCraftWorld* UWorldManager::GetWorldByWorldName(FString SearchWorldName)
{
	for (auto Element : Worlds)
	{
		if (Element->GetCraftWorldName() == SearchWorldName)
		{
			return Element;
		}
	}
	return nullptr;
}


UNativeCraftWorld* UWorldManager::LoadCraftWorldInMemory(TSubclassOf<UNativeCraftWorld> TargetWorld)
{
	TObjectPtr<UNativeCraftWorld> TargetWorldInstance = TargetWorld->GetDefaultObject<UNativeCraftWorld>();


	for (auto Element : Worlds)
	{
		// Do WorldName can not identical
		if (Element->GetCraftWorldName() == TargetWorldInstance->GetCraftWorldName())
		{
			return Element;
		}
	}
	TObjectPtr<UNativeCraftWorld> CraftWorld = NewObject<UNativeCraftWorld>(this, TargetWorld);
	CraftWorld->InitializeWorldInstance();
	Worlds.Add(CraftWorld);
	UE_LOG(LogChamingCraftWorld, Display,
	       TEXT("[🌍] Load CraftWorld In Memory\n"
		       "		World Name: %s"), *CraftWorld->GetCraftWorldName());
	return CraftWorld;
}

UNativeCraftWorld* UWorldManager::GetShownWorld()
{
	for (auto World : Worlds)
	{
		if (World->GetGamePlayWorldInstance()->IsLevelVisible())
		{
			return World;
		}
	}
	return nullptr;
}

bool UWorldManager::UnLoadCraftWorldInMemory(UNativeCraftWorld* TargetWorld)
{
	if (Worlds.Contains(TargetWorld))
	{
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[🌍] UnLoad CraftWorld In Memory\n"
			       "		World Name: %s"), *TargetWorld->GetCraftWorldName());
		TargetWorld->GetGamePlayWorldInstance()->SetShouldBeVisible(false);
		TargetWorld->GetGamePlayWorldInstance()->SetShouldBeLoaded(false);
		Worlds.Remove(TargetWorld);
		return true;
	}
	else
	{
		UE_LOG(LogChamingCraftWorld, Error,
		       TEXT("[🌍] Fail to Unload CraftWorld In Memory\n"
			       "		Worlds Array do not find correspound word"));
		return false;
	}
}

UNativeCraftWorld* UWorldManager::ShownCraftWorld(UNativeCraftWorld* TargetWorld)
{
	for (auto Element : Worlds)
	{
		if (Element == TargetWorld)
		{
			Element->GetGamePlayWorldInstance()->SetShouldBeVisible(true);
		}
		else
		{
			// Auto matically hiddent the worlds that not the target
			HiddenCraftWorld(Element);
		}
	}
	return TargetWorld;
}

UNativeCraftWorld* UWorldManager::HiddenCraftWorld(UNativeCraftWorld* TargetWorld)
{
	TargetWorld->GetGamePlayWorldInstance()->SetShouldBeVisible(false);
	// broadcast hidden event in Craft worlds.
	TargetWorld->OnCraftWorldHidden_Implementation(TargetWorld);
	return TargetWorld;
}

UNativeCraftWorld* UWorldManager::TeleportPlayerToWorld_Internal(ACharacter* PlayerCharacter, FString WorldName,
                                                                 UNativeCraftWorld* TargetWorld)
{
	TObjectPtr<UNativeCraftWorld> TargetCraftWorld;
	if (!WorldName.IsEmpty())
	{
		TargetCraftWorld = GetWorldByWorldName(WorldName);
	}


	if (TargetWorld && WorldName.IsEmpty())
	{
		for (auto Element : Worlds)
		{
			if (TargetWorld == Element)
			{
				TargetCraftWorld = Element;
			}
		}
	}

	if (TargetCraftWorld && TargetCraftWorld->GetGamePlayWorldInstance()->IsLevelVisible())
	{
		if (TargetCraftWorld->GetCraftWorldPlayers().Contains(PlayerCharacter))
		{
			UE_LOG(LogChamingCraftWorld, Error,
			       TEXT("[🌍] Fail to Teleport player to world: %s\n"
				       "		Player Already in the world"), *TargetCraftWorld->GetCraftWorldName());
			return TargetCraftWorld;
		}
		bool TeleportResult = TeleportPlayerToWarp(PlayerCharacter, "Spawn");
		//
		if (TeleportResult)
		{
			TargetCraftWorld->AddPlayerToWorldPlayerList(PlayerCharacter);
			TObjectPtr<UPlayerData> PlayerData = UCoreComponents::GetGameInstance(PlayerCharacter)->GetRuntimeGameData()
				->RuntimeSave.PlayerData;
			PlayerData->PlayerLocation.GameWorld = TargetCraftWorld;
			PlayerData->PlayerLocation.RegionGameWorld = TargetCraftWorld;
		}
	}
	else
	{
		return TargetCraftWorld;
	}

	return TargetCraftWorld;
}

bool UWorldManager::TeleportPlayerToWarp(APawn* PlayerCharacter, const FName WarpPoint)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ACraftWorldWarpPoint::StaticClass(), OutActors);
	for (const auto OutActor : OutActors)
	{
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[🌍]  Find Warp <%s> in world <%s>"), *Cast<ACraftWorldWarpPoint>(OutActor)->TargetName,
		       *PlayerCharacter->GetWorld()->GetName());
		if (Cast<ACraftWorldWarpPoint>(OutActor)->TargetName == WarpPoint)
		{
			//TODO: 未知原因会导致这里发生传送位置不符,初步判断是生命周期问题
			bool bIsSuccessTeleport = PlayerCharacter->SetActorLocation(
				OutActor->GetActorLocation(), false, nullptr, ETeleportType::None);
			if (bIsSuccessTeleport)
			{
				UE_LOG(LogChamingCraftWorld, Display,
				       TEXT("[🌍]  Teleport Player to target warp <%s>"), *WarpPoint.ToString());
			}
			else
			{
				UE_LOG(LogChamingCraftWorld, Error,
				       TEXT("[🌍]  Fail to Teleport Player to target warp <%s>"), *WarpPoint.ToString());
			}
			return true;
		}
	}
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Target warp does not exist, use the default spawn, please check the warp name"));
	return false;
}


AWorldEntityManager* UWorldManager::GetWorldEntityManager()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AWorldEntityManager::StaticClass(), OutActors);
	if (OutActors.Num() > 1)
	{
		UE_LOG(LogChamingCraftWorld, Error,
		       TEXT("[🌍]  Too many WorldEntityManager in the World!\n"
			       "		(❌) You need unload some WorldEntityManager"));
		return nullptr;
	}
	else if (OutActors.IsEmpty())
	{
		UE_LOG(LogChamingCraftWorld, Error,
		       TEXT("[🌍]  No WorldEntityManager in the World!\n"
			       "		(❌) You need add 1 WorldEntityManager in the level"));
		return nullptr;
	}
	for (const auto OutActor : OutActors)
	{
		TObjectPtr<AWorldEntityManager> WorldEntityManagerActor = Cast<AWorldEntityManager>(OutActor);
		if (WorldEntityManagerActor)
		{
			return WorldEntityManagerActor;
		}
	}
	return nullptr;
}


bool UWorldManager::TravelPlayerToWarp(APawn* PlayerCharacter, const FName WarpPoint)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ACraftWorldWarpPoint::StaticClass(), OutActors);
	for (const auto OutActor : OutActors)
	{
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[🌍]  Find Warp <%s> in world <%s>"), *Cast<ACraftWorldWarpPoint>(OutActor)->TargetName,
		       *PlayerCharacter->GetWorld()->GetName());
		if (Cast<ACraftWorldWarpPoint>(OutActor)->TargetName == WarpPoint)
		{
			//TODO: 未知原因会导致这里发生传送位置不符,初步判断是生命周期问题
			bool bIsSuccessTeleport = PlayerCharacter->SetActorLocation(
				OutActor->GetActorLocation(), false, nullptr, ETeleportType::None);
			// TeleportTo(OutActor->GetActorLocation(), FRotator(), false,false);
			// OutActor->GetActorLocation().Equals(PlayerCharacter->GetActorLocation(),10.0f)
			if (bIsSuccessTeleport)
			{
				UE_LOG(LogChamingCraftWorld, Display,
				       TEXT("[🌍]  Teleport Player to target warp <%s>"), *WarpPoint.ToString());
			}
			else
			{
				UE_LOG(LogChamingCraftWorld, Error,
				       TEXT("[🌍]  Fail to Teleport Player to target warp <%s>"), *WarpPoint.ToString());
			}
			return true;
		}
	}
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Target warp does not exist, use the default spawn, please check the warp name"));
	return false;
}


UCharmingCraftInstance* UWorldManager::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(GetOuter());
}

UGameEventHandler* UWorldManager::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}
