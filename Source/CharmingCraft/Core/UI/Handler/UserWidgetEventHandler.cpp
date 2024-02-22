// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetEventHandler.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Save/GamePlayLogicManager.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

void UUserWidgetEventHandler::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	GamePlayLogicManager = GameInstance->GamePlayLogicManager;

	GamePlayLogicManager->OnPlayerOpenInventory.AddDynamic(this, &UUserWidgetEventHandler::OnPlayerOpenInventoryEvent);
	GameInstance->UserWidgetEventHandler = this;
}

void UUserWidgetEventHandler::OnPlayerOpenInventoryEvent_Implementation(ACharacter* Instigator)
{
	UE_LOG(LogChamingCraftWidgetHandler, Display, TEXT("[🔍] OnPlayerOpenInventoryEvent trigger by: %s"),
	       *Instigator->GetName());
}
