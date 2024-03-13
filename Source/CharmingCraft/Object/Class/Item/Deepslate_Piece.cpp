// Fill out your copyright notice in the Description page of Project Settings.


#include "Deepslate_Piece.h"

#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"

UDeepslate_Piece::UDeepslate_Piece()
{
	DisplayName = FText::FromString("Deepslate Piece");
	MaxStackSize = 64;
	ItemType = EItemType::RESOURCE;
	Material = EMaterial::DEEPSLATE_PIECE;
	AssetName = TEXT("deepslate_piece");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString("Deepslate is a hard stone, and there is a very small chance that it will fall when collecting stones.");
	Super::LoadLocalAsset();
}
