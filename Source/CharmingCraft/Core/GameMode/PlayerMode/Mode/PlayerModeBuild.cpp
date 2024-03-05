// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModeBuild.h"

#include "CharmingCraft/Core/Log/Logging.h"

UPlayerModeBuild::UPlayerModeBuild()
{
	ModeName = EPlayerMode::BUILD;
	// /Script/EnhancedInput.InputMappingContext'/Game/CharmingCraft/Input/Actions/BudingInputAction/BuildingInputMappingContext.BuildingInputMappingContext'
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(
		TEXT(
			"InputMappingContext'/Game/CharmingCraft/Input/Actions/BudingInputAction/BuildingInputMappingContext.BuildingInputMappingContext'"));
	if (MappingContextFinder.Succeeded())
	{
		ModeMappingContext = MappingContextFinder.Object;
		UE_LOG(LogChamingCraftCraftGameMode, Display,
		       TEXT("[🎮]  GameMode %s MappingContext  is Loaded"), *EnumClassToString(ModeName));
	}
}
