// Fill out your copyright notice in the Description page of Project Settings.


#include "Lead.h"
#include "../Core/Item/Meta/ItemMeta.h"
#include "AppleItem.h"

ULead::ULead()
{
	DisplayName = FText::FromString("Lead");
	MaxStackSize = 64;
	ItemType = EItemType::MATERIAL;
	Material = EMaterial::LEAD;
	AssetName = TEXT("lead_ingot");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString("It is a heavy metal that is denser than most common materials.");
	Super::LoadLocalAsset();
}
