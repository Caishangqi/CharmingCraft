// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleItem.h"

UAppleItem::UAppleItem()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Apple");
	DescribeText = FText::FromString("Apples are a good source of nutrients, including fiber, vitamin C");
	AssetName = TEXT("apple");
	Material = EMaterial::APPLE;
	ItemMetaClass = UItemMeta::StaticClass();
	
	Super::LoadLocalAsset();
}

void UAppleItem::ConsumeForHealth()
{
}
