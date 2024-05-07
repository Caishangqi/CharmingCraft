// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryWidget.h"

#include "NativePlayerCharacter.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "../Core/Container/Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

void UPlayerInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogChamingCraftWidgetHandler, Display,
	       TEXT("[✅]  Add Inventory: %s to Widget %s "), *ContainInventory->GetName(), *this->GetName());
}

void UPlayerInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
