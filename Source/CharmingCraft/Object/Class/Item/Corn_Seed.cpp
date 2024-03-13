// Fill out your copyright notice in the Description page of Project Settings.


#include "Corn_Seed.h"

#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"

UCorn_Seed::UCorn_Seed()
{
	DisplayName = FText::FromString("Corn seeds");
	MaxStackSize = 64;
	ItemType = EItemType::SEEDS;
	Material = EMaterial::CORN_SEED;
	AssetName = TEXT("corn_seed");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString("One of the most popular grains. The sweet, fresh cobs are a summer favorite.");	
	Super::LoadLocalAsset();
}
