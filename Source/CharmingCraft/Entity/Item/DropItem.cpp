// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"

#include "CharmingCraft/Object/Components/ItemStack.h"

ADropItem::ADropItem()
{
	ItemStack = CreateDefaultSubobject<UItemStack>("Default ItemStack");
}
