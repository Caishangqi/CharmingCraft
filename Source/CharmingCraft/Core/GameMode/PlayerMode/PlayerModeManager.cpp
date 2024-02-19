// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModeManager.h"

UPlayerModeManager::UPlayerModeManager()
{
	// Default
	CurrentPlayerMode = EPlayerMode::Battle;
}

void UPlayerModeManager::ChangePlayerMode(ACharacter* Instigator, EPlayerMode NewPlayerMode)
{
	OnPlayerModeChangeDelegate.Broadcast(Instigator, NewPlayerMode);
}
