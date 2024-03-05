// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModeManager.h"

#include "Mode/PlayerModeBuild.h"
#include "Mode/PlayerModeCombat.h"
#include "Mode/PlayerModeInventory.h"

UPlayerModeManager::UPlayerModeManager()
{
	// Default

	// Add Built-in playermode
	LoadedPlayerMods.Add(EPlayerMode::COMBAT,
	                     NewObject<UPlayerModeCombat>(this, "EPlayerMode::COMBAT")->BindDelegate());
	LoadedPlayerMods.Add(EPlayerMode::INVENTORY,
	                     NewObject<UPlayerModeInventory>(this, "EPlayerMode::INVENTORY")->BindDelegate());
	LoadedPlayerMods.Add(EPlayerMode::BUILD, NewObject<UPlayerModeBuild>(this, "EPlayerMode::BUILD")->BindDelegate());
	CurrentPlayerMode = LoadedPlayerMods.Find(EPlayerMode::COMBAT)->Get(); // set default to combat
}

void UPlayerModeManager::ChangePlayerMode(EPlayerMode FromGameMode, ACharacter* Instigator, EPlayerMode NewPlayerMode)
{
	OnPlayerModeChangeDelegate.Broadcast(FromGameMode, Instigator, NewPlayerMode);
}
