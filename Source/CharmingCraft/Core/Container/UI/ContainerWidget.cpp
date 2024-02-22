// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerWidget.h"

#include "DCharacter.h"

void UContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TObjectPtr<ADCharacter> Player = Cast<ADCharacter>(GetOwningLocalPlayer());
	if (Player)
	{
		ContainInventory = Player->InventoryComponent;
	}
}
