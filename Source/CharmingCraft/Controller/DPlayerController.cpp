// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

#include "DPlayerAIController.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Core/Save/Data/RuntimeGameData.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

ADPlayerController::ADPlayerController()
{
	// Find Default Mapping
	// /Script/EnhancedInput.InputMappingContext'/Game/CharmingCraft/Input/Actions/GlobalInputAction/GlobalInputMappingContext.GlobalInputMappingContext'
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(
		TEXT(
			"InputMappingContext'/Game/CharmingCraft/Input/Actions/GlobalInputAction/GlobalInputMappingContext.GlobalInputMappingContext'"));
	if (MappingContextFinder.Succeeded())
	{
		GlobalMappingContext = MappingContextFinder.Object;
		UE_LOG(LogChamingCraftGameMode, Display,
		       TEXT("[🎮]  Controller %s MappingContext  is Loaded"), *this->GetName());
	}
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
