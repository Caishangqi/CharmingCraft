// Fill out your copyright notice in the Description page of Project Settings.


#include "Copper.h"

UCopper::UCopper()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Copper");
	MaxStackSize = 64;
	ItemType = EItemType::MATERIAL;
	Material = EMaterial::COPPER;
	AssetName = TEXT("copper_ingot");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString("It is a soft, malleable, and ductile metal with very high thermal and electrical conductivity.");	
	Super::LoadLocalAsset();
}
