// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModeInventory.h"

#include "CharmingCraft/Core/Log/Logging.h"

UPlayerModeInventory::UPlayerModeInventory()
{
	ModeName = EPlayerMode::INVENTORY;
	// /Script/EnhancedInput.InputMappingContext'/Game/CharmingCraft/Input/Actions/InventoryInputAction/InventoryInputMappingContext.InventoryInputMappingContext'
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(
		TEXT(
			"InputMappingContext'/Game/CharmingCraft/Input/Actions/InventoryInputAction/InventoryInputMappingContext.InventoryInputMappingContext'"));
	if (MappingContextFinder.Succeeded())
	{
		ModeMappingContext = MappingContextFinder.Object;
		UE_LOG(LogChamingCraftGameMode, Display,
		       TEXT("[🎮]  GameMode %s MappingContext  is Loaded"), *EnumClassToString(ModeName));
	}
}
