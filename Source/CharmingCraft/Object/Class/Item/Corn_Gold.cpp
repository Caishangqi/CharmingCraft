// Fill out your copyright notice in the Description page of Project Settings.


#include "Corn_Gold.h"

#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"

UCorn_Gold::UCorn_Gold()
{
	DisplayName = FText::FromString("Gold Corn");
	MaxStackSize = 64;
	ItemType = EItemType::RESOURCE;
	Material = EMaterial::CORN_GOLD;
	AssetName = TEXT("corn_gold");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString(
		"It is more valuable than ordinary corn and can be used to make advance potions and magic foods.");
	Super::LoadLocalAsset();
}
