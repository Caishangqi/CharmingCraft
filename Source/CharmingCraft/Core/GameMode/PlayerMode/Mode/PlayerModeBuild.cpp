// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModeBuild.h"

#include "CharmingCraft/Core/Builds/Module/BuildModuleManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "GameFramework/Character.h"

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

void UPlayerModeBuild::UpdateControllerMappingContext(EPlayerMode FromGameMode, ACharacter* Instigator,
                                                      EPlayerMode NewPlayerMode)
{
	Super::UpdateControllerMappingContext(FromGameMode, Instigator, NewPlayerMode);
	if (ModeName != NewPlayerMode)
	{
		// Reset Build System
		Cast<UCharmingCraftInstance>(Instigator->GetGameInstance())->GetBuildModuleManager()->StopBuildPreview();
	}
}

void UPlayerModeBuild::OnPlayerModeChangeEvent(EPlayerMode FromGameMode, ACharacter* Instigator,
                                               EPlayerMode NewPlayerMode)
{
	Super::OnPlayerModeChangeEvent(FromGameMode, Instigator, NewPlayerMode);
	if (ModeName != NewPlayerMode)
	{
		TObjectPtr<UCharmingCraftInstance> GameInstance = Cast<UCharmingCraftInstance>(ParentModeManager.GetOuter());
		GameInstance->BuildModuleManager->RestToDefault();
	}
}
