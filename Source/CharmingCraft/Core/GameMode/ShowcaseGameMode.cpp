// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowcaseGameMode.h"

AShowcaseGameMode::AShowcaseGameMode()
{
	DefaultPawnClass = nullptr;
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(
	TEXT("/Game/CharmingCraft/Controller/DPlayerController.DPlayerController_C"));
	if (PlayerControllerClassFinder.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassFinder.Class;
	}
}
