// Fill out your copyright notice in the Description page of Project Settings.


#include "Copper.h"

UCopper::UCopper()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Copper");
	MaxStackSize = 64;
	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(
		TEXT("/Script/Engine.Texture2D'/Game/CharmingCraft/Assets/textures/item/copper_ingot.copper_ingot'"));
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
