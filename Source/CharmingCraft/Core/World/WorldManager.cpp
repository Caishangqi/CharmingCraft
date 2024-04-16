// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "CharmingCraft/Core/Builds/SceneWarpPoint.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Camera/CameraManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Resource/Chunk/LandChunk.h"
#include "CharmingCraft/Core/Save/Data/RuntimeGameData.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameFramework/PlayerStart.h"
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

bool UWorldManager::TeleportPlayerToWarp(APawn* PlayerCharacter, const TSoftObjectPtr<UWorld> TargetLevel,
                                         const FName WarpName)
{
	TArray<AActor*> OutActors;


	// If Player and Target Level are all loaded and visible
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetMapName()))
	{
		const bool IsLevelVisible = LoadedWorlds[TargetLevel.LoadSynchronous()->GetMapName()]->IsLevelVisible();
		if (IsLevelVisible)
		{
			return TeleportPlayerToWarpLocal(PlayerCharacter, WarpName);
		}
		else
		{
			UE_LOG(LogChamingCraftWorld, Error,
			       TEXT("[🌍]  Can not Teleport Player to warp %s\n"
				       "		(❌) Because the TargetLevel is not visible, turn on before teleport"), *WarpName.ToString());
		}
	}
	// If Target level is not loaded
	else
	{
		UE_LOG(LogChamingCraftWorld, Error,
		       TEXT("[🌍]  Can not Teleport Player to warp %s\n"
			       "		(❌) Because the TargetLevel is not loaded, load the level before teleport"),
		       *WarpName.ToString());
		return false;
	}
	return false;
}

bool UWorldManager::TeleportPlayerToWarpLocal(APawn* PlayerCharacter, const FName WarpPoint)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ASceneWarpPoint::StaticClass(), OutActors);
	for (const auto OutActor : OutActors)
	{
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[🌍]  Find Warp %s in world %s"), *Cast<ASceneWarpPoint>(OutActor)->TargetName,
		       *PlayerCharacter->GetWorld()->GetName());
		if (Cast<ASceneWarpPoint>(OutActor)->TargetName == WarpPoint)
		{
			if (Cast<ASceneWarpPoint>(OutActor)->IsInitialized())
			{
				//TODO: 未知原因会导致这里发生传送位置不符,初步判断是生命周期问题
				bool bIsSuccessTeleport = PlayerCharacter->SetActorLocation(
					OutActor->GetActorLocation(), false, nullptr, ETeleportType::None);
				// TeleportTo(OutActor->GetActorLocation(), FRotator(), false,false);
				// OutActor->GetActorLocation().Equals(PlayerCharacter->GetActorLocation(),10.0f)
				if (bIsSuccessTeleport)
				{
					UE_LOG(LogChamingCraftWorld, Display,
					       TEXT("[🌍]  Teleport Player to target Warp: %s"), *WarpPoint.ToString());
				}
				else
				{
					UE_LOG(LogChamingCraftWorld, Error,
					       TEXT("[🌍]  Fail to Teleport Player to target Warp: %s"), *WarpPoint.ToString());
				}

				return true;
			}
			else
			{
				UE_LOG(LogChamingCraftWorld, Error,
				       TEXT(
					       "[🌍]  Fail to Teleport Player to target Warp: %s\n"
					       "			(!) Reason: ASceneWarpPoint is not initialize"), *WarpPoint.ToString());
				//TeleportPlayerToWarpLocal(PlayerCharacter, WarpPoint);
			}
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

FLevelStreamingDynamicResult UWorldManager::TravelPlayerToWorld(APawn* PlayerCharacter,
                                                                const TSoftObjectPtr<UWorld> TargetLevel)
{
	FLevelStreamingDynamicResult LevelStreamingDynamicResult;

	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetName()))
	{
		LevelStreamingDynamicResult.LoadedWorld = LoadedWorlds[TargetLevel->GetName()];
		LevelStreamingDynamicResult.IsSuccess = TeleportPlayerToWarpLocal(PlayerCharacter, "Spawn");
		if (LevelStreamingDynamicResult.IsSuccess)
		{
			UE_LOG(LogChamingCraftWorld, Display,
			       TEXT("[🌍]  Travel Player to target World: %s"), *TargetLevel.LoadSynchronous()->GetName());
			GetGameInstance_Implementation()->GetCameraManager()->SwitchPlayerCameraView(PlayerCharacter, ECameraPerspectiveEnum::INCLINE);
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

FLevelStreamingDynamicResult UWorldManager::LoadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel,
                                                              bool UnloadRemainWorld)
{
	FLevelStreamingDynamicResult LevelStreamingDynamicResult;
	
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetMapName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel.LoadSynchronous()->GetName()];
		LevelStreamingDynamic->SetShouldBeVisible(true);
		LevelStreamingDynamicResult.IsSuccess = true;
		LevelStreamingDynamicResult.LoadedWorld = LevelStreamingDynamic;
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
		LevelStreamingDynamicResult.LoadedWorld = LevelStreamingDynamic;
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

FLevelStreamingDynamicResult UWorldManager::UnloadWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel)
{
	FLevelStreamingDynamicResult LevelStreamingDynamicResult;
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel.LoadSynchronous()->GetName()];
		LevelStreamingDynamic->SetShouldBeVisible(false);
		LevelStreamingDynamicResult.LoadedWorld = LevelStreamingDynamic;
		LevelStreamingDynamicResult.IsSuccess = true;
		GetGameEventHandler_Implementation()->OnUnloadGameLevelStartEvent(this, TargetLevel.LoadSynchronous());
		return LevelStreamingDynamicResult;
	}
	return LevelStreamingDynamicResult;
}

FLevelStreamingDynamicResult UWorldManager::UnloadAndRemoveWorldInstance(const TSoftObjectPtr<UWorld> TargetLevel)
{
	FLevelStreamingDynamicResult LevelStreamingDynamicResult;
	if (LoadedWorlds.Contains(TargetLevel.LoadSynchronous()->GetName()))
	{
		ULevelStreamingDynamic* LevelStreamingDynamic = LoadedWorlds[TargetLevel->GetName()];
		LevelStreamingDynamic->SetShouldBeVisible(false);
		LevelStreamingDynamic->SetShouldBeLoaded(false);
		LevelStreamingDynamicResult.LoadedWorld = nullptr;
		LevelStreamingDynamicResult.IsSuccess = true;
		return LevelStreamingDynamicResult;
	}
	return LevelStreamingDynamicResult;
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
	return GetGameInstance_Implementation()->GetGameEventHandler();
}
