// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryWidget.h"

#include "DCharacter.h"

void UPlayerInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TObjectPtr<ADCharacter> Player = Cast<ADCharacter>(GetOwningPlayer()->GetPawn());
	if (Player)
	{
		ContainInventory = Player->InventoryComponent;
	}
}

void UPlayerInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
