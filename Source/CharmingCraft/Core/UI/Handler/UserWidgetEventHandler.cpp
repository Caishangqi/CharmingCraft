// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetEventHandler.h"

#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/UI/Holder/WidgetHolder.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

void UUserWidgetEventHandler::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	GamePlayLogicManager = GameInstance->GamePlayLogicManager;

	GamePlayLogicManager->OnPlayerOpenInventory.AddDynamic(this, &UUserWidgetEventHandler::OnPlayerOpenInventoryEvent);
	GamePlayLogicManager->OnPlayerOpenContainer.AddDynamic(this, &UUserWidgetEventHandler::OnPlayerOpenContainerEvent);
	GamePlayLogicManager->OnPlayerClickMove.AddDynamic(this, &UUserWidgetEventHandler::OnPlayerClickMoveEvent);
	GamePlayLogicManager->OnItemDetailDisplay.AddDynamic(this, &UUserWidgetEventHandler::OnItemDetailDisplayEvent);
	GamePlayLogicManager->OnCloseWidget.AddDynamic(this, &UUserWidgetEventHandler::OnCloseWidgetEvent);
	GamePlayLogicManager->OnPlayerOpenTravelMap.AddDynamic(this, &UUserWidgetEventHandler::OnPlayerOpenTravelMapEvent);
	GamePlayLogicManager->OnOpenWidget.AddDynamic(this, &UUserWidgetEventHandler::OnOpenWidgetEvent);
	GamePlayLogicManager->OnPlayerOpenCraftPannel.AddDynamic(this, &UUserWidgetEventHandler::OnPlayerOpenCraftPannelEvent);

	LoadedUserWidget.SetNum(100);

	GameInstance->UserWidgetEventHandler = this;
}

bool UUserWidgetEventHandler::CloseWidgetByClass(TSubclassOf<UWidgetHolder> TargetWidgetHolder)
{
	for (auto Element : LoadedUserWidget)
	{
		if (Element.IsA(TargetWidgetHolder.Get()))
		{
			Cast<UWidgetHolder>(Element)->RemoveWidget_Implementation();
			return true;
		}
	}
	return false;
}

void UUserWidgetEventHandler::OnPlayerOpenCraftPannelEvent_Implementation(ACharacter* Instigator, UObject* Creator)
{
}

void UUserWidgetEventHandler::OnOpenWidgetEvent_Implementation(UObject* Instigator, UUserWidget* TargetWidget)
{
}


void UUserWidgetEventHandler::OnPlayerOpenTravelMapEvent_Implementation(ACharacter* Instigator, UObject* Creator)
{
	UE_LOG(LogChamingCraftWidgetHandler, Display, TEXT("[🔍] OnPlayerOpenTravelMapEvent trigger by: %s"),
	       *Instigator->GetName());
}


void UUserWidgetEventHandler::OnCloseWidgetEvent_Implementation(UObject* Instigator, UUserWidget* TargetWidget)
{
	UE_LOG(LogChamingCraftWidgetHandler, Display,
	       TEXT("[❕] OnCloseWidgetEvent trigger by: %s Target Widget: %s"),
	       *Instigator->GetName(), *TargetWidget->GetName());
	TargetWidget->RemoveFromParent();
	//LoadedUserWidget.Remove(TargetWidget);
}

void UUserWidgetEventHandler::OnItemDetailDisplayEvent_Implementation(UItemStack* ItemToDisplay, UObject* Creator)
{
	if (ItemToDisplay)
	{
		UE_LOG(LogChamingCraftWidgetHandler, Display,
		       TEXT("[❕] OnItemDetailDisplayEvent trigger by: %s Target Item: %s"),
		       *Creator->GetName(), *ItemToDisplay->ItemMeta->DisplayName);
	}
}

void UUserWidgetEventHandler::OnPlayerClickMoveEvent_Implementation(ACharacter* Instigator, FVector TargetLocation)
{
	// UE_LOG(LogChamingCraftWidgetHandler, Display,
	//        TEXT("[🔍] OnPlayerClickMoveEvent trigger by: %s Target Location: %s"),
	//        *Instigator->GetName(), *TargetLocation.ToString());
}

void UUserWidgetEventHandler::OnPlayerOpenContainerEvent_Implementation(ACharacter* Instigator,
                                                                        UInventoryComponent* TargetContainer,
                                                                        UObject* Creator)
{
	if (Instigator && TargetContainer)
	{
		UE_LOG(LogChamingCraftWidgetHandler, Display,
		       TEXT("[🔍] OnPlayerOpenContainerEvent trigger by: %s Target Container: %s"),
		       *Instigator->GetName(), *TargetContainer->GetName());
	}
}

void UUserWidgetEventHandler::OnPlayerOpenInventoryEvent_Implementation(ACharacter* Instigator, UObject* Creator)
{
	UE_LOG(LogChamingCraftWidgetHandler, Display, TEXT("[🔍] OnPlayerOpenInventoryEvent trigger by: %s"),
	       *Instigator->GetName());
}
