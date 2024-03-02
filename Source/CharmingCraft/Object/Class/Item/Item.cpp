// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
	MaxStackSize = 64;
}

void UItem::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator)
{
}

void UItem::EndItemInteract()
{
}
