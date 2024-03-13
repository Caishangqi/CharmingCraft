// Fill out your copyright notice in the Description page of Project Settings.


#include "Cobalt.h"

UCobalt::UCobalt()
{
	DisplayName = FText::FromString("Cobalt");
	MaxStackSize = 64;
	ItemType = EItemType::MATERIAL;
	Material = EMaterial::COBALT;
	AssetName = TEXT("cobalt_ingot");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString(
		"Cobalt is a lustrous very hard silvery metal belonging to a group called the \"transition metals\".");
	Super::LoadLocalAsset();
}
