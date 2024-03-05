// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModeCombat.h"

#include "CharmingCraft/Core/GameMode/Enum/EPlayerMode.h"
#include "CharmingCraft/Core/Log/Logging.h"

UPlayerModeCombat::UPlayerModeCombat()
{
	ModeName = EPlayerMode::COMBAT;
	// /Script/EnhancedInput.InputMappingContext'/Game/CharmingCraft/Input/Actions/CombatInputAction/CombatInputMappingContext.CombatInputMappingContext'
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(
		TEXT(
			"InputMappingContext'/Game/CharmingCraft/Input/Actions/CombatInputAction/CombatInputMappingContext.CombatInputMappingContext'"));
	if (MappingContextFinder.Succeeded())
	{
		ModeMappingContext = MappingContextFinder.Object;
		UE_LOG(LogChamingCraftCraftGameMode, Display,
		       TEXT("[🎮]  GameMode %s MappingContext  is Loaded"), *EnumClassToString(ModeName));
	}
}
