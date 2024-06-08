// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeUserWidgetEventHandler.h"

#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/UI/Holder/WidgetHolder.h"
#include "../Core/CharmingCraftInstance.h"

void UNativeUserWidgetEventHandler::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	GamePlayLogicManager = GameInstance->GamePlayLogicManager;

	GamePlayLogicManager->OnPlayerOpenInventory.AddDynamic(
		this, &UNativeUserWidgetEventHandler::OnPlayerOpenInventoryEvent);
	GamePlayLogicManager->OnPlayerOpenContainer.AddDynamic(
		this, &UNativeUserWidgetEventHandler::OnPlayerOpenContainerEvent);
	GamePlayLogicManager->OnPlayerClickMove.AddDynamic(this, &UNativeUserWidgetEventHandler::OnPlayerClickMoveEvent);
	GamePlayLogicManager->OnItemDetailDisplay.
	                      AddDynamic(this, &UNativeUserWidgetEventHandler::OnItemDetailDisplayEvent);
	GamePlayLogicManager->OnCloseWidget.AddDynamic(this, &UNativeUserWidgetEventHandler::OnCloseWidgetEvent);
	GamePlayLogicManager->OnPlayerOpenTravelMap.AddDynamic(
		this, &UNativeUserWidgetEventHandler::OnPlayerOpenTravelMapEvent);
	GamePlayLogicManager->OnOpenWidget.AddDynamic(this, &UNativeUserWidgetEventHandler::OnOpenWidgetEvent);
	GamePlayLogicManager->OnPlayerOpenCraftPannel.AddDynamic(
		this, &UNativeUserWidgetEventHandler::OnPlayerOpenCraftPannelEvent);

	GameInstance->UserWidgetEventHandler = this;
}

bool UNativeUserWidgetEventHandler::CloseWidgetByClass(TSubclassOf<UWidgetHolder> TargetWidgetHolder)
{
	TArray<UUserWidget*> TargetClassWidget;
	bool bHasRemoveWidget = false;

	for (auto Element : LoadedUserWidget)
	{
		if (Element.IsA(TargetWidgetHolder.Get()))
		{
			TargetClassWidget.Add(Element);
			bHasRemoveWidget = true;
		}
	}

	for (auto ClassWidget : TargetClassWidget)
	{
		ICommonUI::Execute_RemoveWidget(ClassWidget);
	}
	return bHasRemoveWidget;
}

void UNativeUserWidgetEventHandler::OnPlayerOpenCraftPannelEvent_Implementation(
	ACharacter* Instigator, UObject* Creator)
{
}

void UNativeUserWidgetEventHandler::OnOpenWidgetEvent_Implementation(UObject* Instigator, UUserWidget* TargetWidget)
{
}


void UNativeUserWidgetEventHandler::OnPlayerOpenTravelMapEvent_Implementation(ACharacter* Instigator, UObject* Creator)
{
	UE_LOG(LogChamingCraftWidgetHandler, Display, TEXT("[🔍] OnPlayerOpenTravelMapEvent trigger by: %s"),
	       *Instigator->GetName());
}


void UNativeUserWidgetEventHandler::OnCloseWidgetEvent_Implementation(UObject* Instigator, UUserWidget* TargetWidget)
{
	UE_LOG(LogChamingCraftWidgetHandler, Display,
	       TEXT("[❕] OnCloseWidgetEvent trigger by: %s Target Widget: %s"),
	       *Instigator->GetName(), *TargetWidget->GetName());
	TargetWidget->RemoveFromParent();
	//LoadedUserWidget.Remove(TargetWidget);
}

void UNativeUserWidgetEventHandler::OnItemDetailDisplayEvent_Implementation(UItemStack* ItemToDisplay, UObject* Creator)
{
	if (ItemToDisplay)
	{
		UE_LOG(LogChamingCraftWidgetHandler, Display,
		       TEXT("[❕] OnItemDetailDisplayEvent trigger by: %s Target Item: %s"),
		       *Creator->GetName(), *ItemToDisplay->ItemMeta->DisplayName);
	}
}

void UNativeUserWidgetEventHandler::OnPlayerClickMoveEvent_Implementation(
	ACharacter* Instigator, FVector TargetLocation)
{
	// UE_LOG(LogChamingCraftWidgetHandler, Display,
	//        TEXT("[🔍] OnPlayerClickMoveEvent trigger by: %s Target Location: %s"),
	//        *Instigator->GetName(), *TargetLocation.ToString());
}

void UNativeUserWidgetEventHandler::OnPlayerOpenContainerEvent_Implementation(ACharacter* Instigator,
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

void UNativeUserWidgetEventHandler::OnPlayerOpenInventoryEvent_Implementation(ACharacter* Instigator, UObject* Creator)
{
	UE_LOG(LogChamingCraftWidgetHandler, Display, TEXT("[🔍] OnPlayerOpenInventoryEvent trigger by: %s"),
	       *Instigator->GetName());
}
