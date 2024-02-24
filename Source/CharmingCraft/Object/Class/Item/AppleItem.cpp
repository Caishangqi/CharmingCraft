﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleItem.h"

UAppleItem::UAppleItem()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Apple");
	DescribeText = FText::FromString("Apples are a good source of nutrients, including fiber, vitamin C");
	 
	Material = EMaterial::APPLE;
	ItemMetaClass = UItemMeta::StaticClass();
	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(
		TEXT("/Script/Engine.Texture2D'/Game/CharmingCraft/Assets/textures/item/apple.apple'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTexture(
		TEXT("/Script/Engine.StaticMesh'/Game/CharmingCraft/Assets/models/item/apple.apple'"));
	if (IconTexture.Succeeded() && MeshTexture.Succeeded())
	{
		Icon = IconTexture.Object;
		StaticMesh = MeshTexture.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Icon texture!"));
	}
}

void UAppleItem::ConsumeForHealth()
{
}
