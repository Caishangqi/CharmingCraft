// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocks.h"

#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"
#include "CharmingCraft/Core/Log/Logging.h"

URocks::URocks()
{
	DisplayName = FText::FromString("Rocks");
	MaxStackSize = 64;
	ItemType = EItemType::RESOURCE;
	Material = EMaterial::ROCKS;
	AssetName = TEXT("rocks");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString("Rocks are all around us. They make up the backbones of hills and mountains and the foundations of plains and valleys.");	
	Super::LoadLocalAsset();
}
