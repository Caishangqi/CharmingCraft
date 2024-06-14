// Fill out your copyright notice in the Description page of Project Settings.

#include "NativeCraftWorld.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Camera/CameraManager.h"
#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"


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
	UE_LOG(LogChamingCraftWorld, Warning, TEXT("		States: %hhd"), IsSuccess);
	return IsSuccessLoadWorldInstance;
}

FString UNativeCraftWorld::GetCraftWorldName()
{
	return WorldName;
}

TSet<ACharacter*> UNativeCraftWorld::GetCraftWorldPlayers()
{
	return PlayerList;
}

TSoftObjectPtr<UWorld> UNativeCraftWorld::GetCraftWorldMapRes()
{
	return WorldMap;
}


TSet<ACraftWorldWarpPoint*> UNativeCraftWorld::GetLoadedWarpPoints()
{
	return LoadedWarpPoints;
}

ULevelStreamingDynamic* UNativeCraftWorld::GetGamePlayWorldInstance()
{
	return GamePlayWorldInstance;
}

ECameraPerspectiveEnum UNativeCraftWorld::GetTargetCameraPerspective()
{
	return TargetCameraPerspective;
}

TSet<ACharacter*> UNativeCraftWorld::AddPlayerToWorldPlayerList(ACharacter* Player)
{
	if (PlayerList.Contains(Player))
	{
		return PlayerList;
	}
	else
	{
		UCoreComponents::GetGameEventHandler(Player)->OnPlayerJoinWorldEvent(Player, this);
		return PlayerList;
	}
}

TSet<ACharacter*> UNativeCraftWorld::RemovePlayerFromWorldPlayerList(ACharacter* Player)
{
	if (PlayerList.Contains(Player))
	{
		UCoreComponents::GetGameEventHandler(Player)->OnPlayerLeftWorldEvent(Player, this);
		return PlayerList;
	}
	else
	{
		return PlayerList;
	}
}

void UNativeCraftWorld::OnCraftWorldHidden_Implementation(UNativeCraftWorld* TargetWorld)
{
	for (auto Element : PlayerList)
	{
		OnPlayerLeftWorld_Implementation(Element, TargetWorld);
	}
	PlayerList.Empty();
}

void UNativeCraftWorld::OnPlayerLeftWorld_Implementation(ACharacter* Instigator, UNativeCraftWorld* TargetWorld)
{
	if (TargetWorld == this)
	{
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[❕] OnPlayerLeftWorldEvent Player: <%s> LeftedWorld: <%s>"
		       ), *Instigator->GetName(), *TargetWorld->WorldName);

		// TODO: Shoud use event to Trigger player state: such as invisible/ hidden in game
	}
}


void UNativeCraftWorld::OnPlayerJoinWorld_Implementation(ACharacter* Instigator, UNativeCraftWorld* TargetWorld)
{
	if (TargetWorld == this)
	{
		PlayerList.Add(Instigator);
		UE_LOG(LogChamingCraftWorld, Warning,
		       TEXT("[❕] OnPlayerJoinWorldEvent Player: <%s> JoinedWorld: <%s>"
		       ), *Instigator->GetName(), *TargetWorld->WorldName);
		UCoreComponents::GetCameraManager(Instigator)->SwitchPlayerCameraView(Instigator, TargetCameraPerspective);
		FTimerHandle EffectTimer;
		Instigator->GetWorld()->GetTimerManager().SetTimer(EffectTimer, [this,Instigator]
		{
			UGameplayStatics::GetPlayerCameraManager(Instigator, 0)->StartCameraFade
			(1.0f, 0.0f, 1.0f, FColor::Black, false,
			 true);
		}, 0.5f, false);
	}
}
