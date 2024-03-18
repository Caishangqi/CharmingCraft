// Fill out your copyright notice in the Description page of Project Settings.


#include "Corn.h"

#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"

UCorn::UCorn()
{
	DisplayName = FText::FromString("Corn");
	MaxStackSize = 64;
	ItemType = EItemType::RESOURCE;
	Material = EMaterial::CORN;
	AssetName = TEXT("corn");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString(
		"The corn grew waist-high in the fields. The corn was stored in large sacks. The corn was cut and tied in sheaves.");
	Super::LoadLocalAsset();
}
