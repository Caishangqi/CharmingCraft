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

FCharmingCraftWorld UWorldManager::GetPlayerCurrentLevel(ACharacter* PlayerCharacter)
{
	FCharmingCraftWorld LevelStreamingDynamicResult;
	TObjectPtr<UPlayerData> PlayerData = GetGameInstance_Implementation()->GetRuntimeGameData()->RuntimeSave.PlayerData;
	if (GetWorldIsVisible(PlayerData->PlayerLocation.Level))
	{
		LevelStreamingDynamicResult.GamePlayWorld = LoadedWorlds[PlayerData->PlayerLocation.Level.LoadSynchronous()->
		                                                                     GetName()];
		LevelStreamingDynamicResult.IsSuccess = true;
	}
	else if (PlayerData->PlayerSceneLocation.Level)
	{
		LevelStreamingDynamicResult.GamePlayWorld = LoadedWorlds[PlayerData->PlayerSceneLocation.Level->GetName()];
		LevelStreamingDynamicResult.IsSuccess = true;
	}
	return LevelStreamingDynamicResult;
}

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
			//Element->CheckCraftWorldStatus();
		}
		else
		{
			HiddenCraftWorld(Element);
		}
	}
	return TargetWorld;
}

UNativeCraftWorld* UWorldManager::HiddenCraftWorld(UNativeCraftWorld* TargetWorld)
{
	TargetWorld->GetGamePlayWorldInstance()->SetShouldBeVisible(false);
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

void UWorldManager::OnLevelLoadedCallback()
{
	OnLevelLoaded.Broadcast();
}

FCharmingCraftWorld UWorldManager::TravelPlayerToWorld(APawn* PlayerCharacter,
                                                       const TSoftObjectPtr<UWorld> TargetLevel)
{
	FCharmingCraftWorld LevelStreamingDynamicResult;

	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetName()))
	{
		LevelStreamingDynamicResult.GamePlayWorld = LoadedWorlds[TargetLevel->GetName()];
		LevelStreamingDynamicResult.IsSuccess = TravelPlayerToWarp(PlayerCharacter, "Spawn");
		if (LevelStreamingDynamicResult.IsSuccess)
		{
			UE_LOG(LogChamingCraftWorld, Display,
			       TEXT("[🌍]  Travel Player to target World: %s"), *TargetLevel.LoadSynchronous()->GetName());
			GetGameInstance_Implementation()->GetCameraManager()->SwitchPlayerCameraView(
				PlayerCharacter, ECameraPerspectiveEnum::INCLINE);
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
				1.0f, 0.0f, 2.0f, FColor::Black, false, true);
			PlayerCharacter->SetActorHiddenInGame(false); // Make Player visible in game
			GetGameInstance_Implementation()->GetRuntimeGameData()->RuntimeSave.PlayerData->PlayerLocation.Level =
				TargetLevel;
			GetGameEventHandler_Implementation()->OnPlayerTravelToRegionEvent(
				PlayerCharacter, TargetLevel.LoadSynchronous());
		}
	}
	// TODO: Unbind the OnShown Delegate prevent multiple trigger
	return LevelStreamingDynamicResult;
}

FCharmingCraftWorld UWorldManager::TravelPlayerToScene(APawn* PlayerCharacter,
                                                       const TSoftObjectPtr<UWorld> TargetScene,
                                                       FName WarpPoint, bool ResetSceneData)
{
	FCharmingCraftWorld LevelStreamingDynamicResult;
	if (LoadedWorlds.Contains(TargetScene.LoadSynchronous()->GetName()))
	{
		LevelStreamingDynamicResult.GamePlayWorld = LoadedWorlds[TargetScene->GetName()];
		LevelStreamingDynamicResult.IsSuccess = LevelStreamingDynamicResult.IsSuccess = TravelPlayerToWarp(
			PlayerCharacter, WarpPoint);
		if (LevelStreamingDynamicResult.IsSuccess)
		{
			TObjectPtr<UPlayerData> PlayerData = GetGameInstance_Implementation()->GetRuntimeGameData()->RuntimeSave.
				PlayerData;
			UE_LOG(LogChamingCraftWorld, Display,
			       TEXT("[🌍]  Travel Player to target Scene: %s"), *TargetScene.LoadSynchronous()->GetName());
			if (ResetSceneData)
			{
				PlayerData->PlayerSceneLocation.Level = nullptr;
			}
			else
			{
				PlayerData->PlayerSceneLocation.Level = TargetScene;
			}
		}
	}
	return LevelStreamingDynamicResult;
}


FCharmingCraftWorld UWorldManager::LoadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel,
                                                     bool UnloadRemainWorld)
{
	FCharmingCraftWorld LevelStreamingDynamicResult;

	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetMapName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel.LoadSynchronous()->GetName()];
		LevelStreamingDynamic->SetShouldBeVisible(true);
		LevelStreamingDynamicResult.IsSuccess = true;
		LevelStreamingDynamicResult.GamePlayWorld = LevelStreamingDynamic;
		GetGameEventHandler_Implementation()->OnLoadGameLevelStartEvent(this, TargetLevel.LoadSynchronous());
		if (UnloadRemainWorld)
		{
			UnloadAllWorldInstance(TargetLevel);
		}
		return LevelStreamingDynamicResult;
	}

	bool IsSuccess;
	ULevelStreamingDynamic* LevelStreamingDynamic = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
		this, TargetLevel, FVector(0, 0, 0), FRotator(0, 0, 0), IsSuccess);
	if (LevelStreamingDynamic != nullptr)
	{
		LevelStreamingDynamic->OnLevelLoaded.AddUniqueDynamic(this, &UWorldManager::OnLevelLoadedCallback);
	}
	if (IsSuccess)
	{
		LoadedWorlds.Add(TargetLevel.LoadSynchronous()->GetName(), LevelStreamingDynamic);
		LevelStreamingDynamicResult.GamePlayWorld = LevelStreamingDynamic;
		LevelStreamingDynamicResult.IsSuccess = true;
		GetGameEventHandler_Implementation()->OnLoadGameLevelStartEvent(this, TargetLevel.LoadSynchronous());
		if (UnloadRemainWorld)
		{
			UnloadAllWorldInstance(TargetLevel);
		}
		return LevelStreamingDynamicResult;
	}
	return LevelStreamingDynamicResult;
}

bool UWorldManager::UnloadAllWorldInstance(const TSoftObjectPtr<UWorld> WhiteListLevel)
{
	if (WhiteListLevel)
	{
		for (auto Element : LoadedWorlds)
		{
			if (Element.Key != WhiteListLevel.LoadSynchronous()->GetName())
			{
				Element.Value->SetShouldBeVisible(false);
			}
		}
		return true;
	}
	else
	{
		for (auto Element : LoadedWorlds)
		{
			Element.Value->SetShouldBeVisible(false);
		}
		return false;
	}
}

FCharmingCraftWorld UWorldManager::UnloadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel)
{
	FCharmingCraftWorld LevelStreamingDynamicResult;
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel.LoadSynchronous()->GetName()];
		LevelStreamingDynamic->SetShouldBeVisible(false);
		LevelStreamingDynamicResult.GamePlayWorld = LevelStreamingDynamic;
		LevelStreamingDynamicResult.IsSuccess = true;
		GetGameEventHandler_Implementation()->OnUnloadGameLevelStartEvent(this, TargetLevel.LoadSynchronous());
		return LevelStreamingDynamicResult;
	}
	return LevelStreamingDynamicResult;
}

FCharmingCraftWorld UWorldManager::UnloadAndRemoveWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel)
{
	FCharmingCraftWorld LevelStreamingDynamicResult;
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel->GetName()];
		LevelStreamingDynamic->SetShouldBeVisible(false);
		LevelStreamingDynamic->SetShouldBeLoaded(false);
		LevelStreamingDynamicResult.GamePlayWorld = nullptr;
		LevelStreamingDynamicResult.IsSuccess = true;
		return LevelStreamingDynamicResult;
	}
	return LevelStreamingDynamicResult;
}

bool UWorldManager::GetWorldIsVisible(const TSoftObjectPtr<UWorld> TargetLevel)
{
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetName()))
	{
		return LoadedWorlds[TargetLevel.LoadSynchronous()->GetName()]->ShouldBeVisible();
	}
	return false;
}


bool UWorldManager::UnloadWorldChunk(UObject* Instigator, ALandChunk* TargetChunk)
{
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Unloading Chunks form world\n"
		       "		[I] Instigator: %s\n"
		       "		[C] Target Chunk: %s"), *Instigator->GetName(), *TargetChunk->GetName());
	GetGameEventHandler()->OnUnloadWorldChunkEvent(Instigator, TargetChunk);
	return true; // 12
}

UCharmingCraftInstance* UWorldManager::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(GetOuter());
}

UGameEventHandler* UWorldManager::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}
