// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleItem.h"

UAppleItem::UAppleItem()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Apple");
	MaxStackSize = 64;
	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(
		TEXT("/Script/Engine.Texture2D'/Game/CharmingCraft/Assets/textures/item/apple.apple'"));
	if (IconTexture.Succeeded())
	{
		Icon = IconTexture.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Icon texture!"));
	}
}

void UAppleItem::ConsumeForHealth()
{
}
