// Fill out your copyright notice in the Description page of Project Settings.


#include "Ruby.h"

#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"

URuby::URuby()
{
	DisplayName = FText::FromString("Ruby");
	MaxStackSize = 64;
	ItemType = EItemType::RESOURCE;
	Material = EMaterial::RUBY;
	AssetName = TEXT("ruby");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString("Ruby is the most valuable variety of the corundum mineral species");	
	Super::LoadLocalAsset();
}
