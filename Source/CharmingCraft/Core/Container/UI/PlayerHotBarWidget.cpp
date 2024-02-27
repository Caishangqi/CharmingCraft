// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHotBarWidget.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

UPlayerHotBarWidget::UPlayerHotBarWidget()
{
}

void UPlayerHotBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//const UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(GetOuter()->GetWorld()->GetGameInstance());
	//Cast<ADCharacter>(GetOwningLocalPlayer());
	TObjectPtr<ADCharacter> Player = Cast<ADCharacter>(GetOwningPlayer()->GetPawn());
	// UE_LOG(LogChamingCraftGameEvent, Display,
	// 	   TEXT("[!]  UPlayerHotBarWidget::NativeConstruct() %s"),*Player->GetName());
	if (Player)
	{
		ContainInventory = Player->InventoryComponent;
	}
}
