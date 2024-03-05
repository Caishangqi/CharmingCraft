// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerModeBase.h"
#include "CharmingCraft/Core/GameMode/PlayerMode/PlayerModeManager.h"
#include "EnhancedInputSubsystems.h"
#include "CharmingCraft/Controller/DPlayerController.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "GameFramework/Character.h"

UPlayerModeBase::UPlayerModeBase()
{
	ParentModeManager = Cast<UPlayerModeManager>(GetOuter());
}

void UPlayerModeBase::UpdateControllerMappingContext(EPlayerMode FromGameMode, ACharacter* Instigator,
                                                     EPlayerMode NewPlayerMode)
{
	TObjectPtr<ADPlayerController> PlayerController = Cast<ADPlayerController>(Instigator->GetController());
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (ModeName == NewPlayerMode)
	{
		if (LocalPlayer)
		{
			UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<
				UEnhancedInputLocalPlayerSubsystem>();
			if (InputSystem)
			{
				//InputSystem->AddMappingContext(ModeMappingContext.LoadSynchronous(), 0);
				InputSystem->AddMappingContext(ModeMappingContext.LoadSynchronous(), 0);
				UE_LOG(LogChamingCraftCraftGameMode, Display,
				       TEXT("[🎮]  GameMode %s MappingContext is inject to Controller"),
				       *EnumClassToString(ModeName));
			}
		}
	}
	else
	{
		if (LocalPlayer)
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<
				UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(ModeMappingContext.LoadSynchronous());
				UE_LOG(LogChamingCraftCraftGameMode, Display,
				       TEXT("[🎮]  GameMode %s MappingContext is remove from Controller"),
				       *EnumClassToString(ModeName));
			}
		}
	}
}

UPlayerModeBase* UPlayerModeBase::BindDelegate()
{
	ParentModeManager->OnPlayerModeChangeDelegate.AddDynamic(this, &UPlayerModeBase::UpdateControllerMappingContext);
	return this;
}
