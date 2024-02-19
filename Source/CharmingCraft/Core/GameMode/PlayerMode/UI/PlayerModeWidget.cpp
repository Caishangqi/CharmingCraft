// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerModeWidget.h"

#include "CharmingCraft/Core/GameMode/PlayerMode/PlayerModeManager.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

void UPlayerModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// 获取GameInstance
	const UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	PlayerModeManager = GameInstance->GetPlayerModeManager();
	PlayerModeManager->OnPlayerModeChangeDelegate.AddDynamic(this, &UPlayerModeWidget::OnPlayerModeChangeEvent);
}

void UPlayerModeWidget::OnPlayerModeChangeEvent(ACharacter* Instigator, EPlayerMode ToMode)
{
}
