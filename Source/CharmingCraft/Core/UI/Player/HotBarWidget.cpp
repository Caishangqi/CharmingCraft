// Fill out your copyright notice in the Description page of Project Settings.


#include "HotBarWidget.h"

#include "CharmingCraft/Core/GameMode/PlayerMode/PlayerModeManager.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Components/Overlay.h"

void UHotBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	PlayerModeManager = GameInstance->GetPlayerModeManager();
	PlayerModeManager->OnPlayerModeChangeDelegate.AddDynamic(this, &UHotBarWidget::DisplayHotBarByGameMode);
}

