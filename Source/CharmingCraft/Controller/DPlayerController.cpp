// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "DPlayerAIController.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

ADPlayerController::ADPlayerController()
{
}

void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UCharmingCraftInstance>(GetGameInstance());
	GamePlayLogicManager = GameInstance->GetGameEventHandler();
	if (!GameInstance->GetSaveManager()->GetCurrentSaveSlot().IsIndicateBound)
	{
		GameInstance->GetRuntimeGameData()->PlayerCharacter = GetCharacter();
	}
}
