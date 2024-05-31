// Copyright Epic Games, Inc. All Rights Reserved.


#include "NativeCCGameModeBase.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "CharmingCraft/Controller/DPlayerController.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Core/Dungeon/NativeDungeonHandler.h"

ANativeCCGameModeBase::ANativeCCGameModeBase()
{
	// 使用FClassFinder查找蓝图类
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/CharmingCraft/PlayerCharacter.PlayerCharacter_C"));
	if (PlayerPawnClassFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}


	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(
		TEXT("/Game/CharmingCraft/Controller/DPlayerController.DPlayerController_C"));
	if (PlayerControllerClassFinder.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassFinder.Class;
	}
}



void ANativeCCGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogChamingCraftWorld, Error,
	       TEXT("[🌍]  ANativeCCGameModeBase::BeginPlay()"));
}
