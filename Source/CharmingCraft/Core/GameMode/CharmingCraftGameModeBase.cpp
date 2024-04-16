// Copyright Epic Games, Inc. All Rights Reserved.


#include "CharmingCraftGameModeBase.h"

#include "DCharacter.h"
#include "CharmingCraft/Controller/DPlayerController.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

ACharmingCraftGameModeBase::ACharmingCraftGameModeBase()
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
