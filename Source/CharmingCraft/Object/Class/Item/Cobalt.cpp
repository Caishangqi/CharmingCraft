// Fill out your copyright notice in the Description page of Project Settings.


#include "Cobalt.h"

UCobalt::UCobalt()
{
	DisplayName = FText::FromString("Cobalt");
	MaxStackSize = 64;
	ItemType = EItemType::MATERIAL;
	DescribeText = FText::FromString("Cobalt is a lustrous very hard silvery metal belonging to a group called the \"transition metals\".");
	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(
		TEXT("/Script/Engine.Texture2D'/Game/CharmingCraft/Assets/textures/item/cobalt_ingot.cobalt_ingot'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTexture(
		TEXT("/Script/Engine.StaticMesh'/Game/CharmingCraft/Assets/models/item/cobalt_ingot.cobalt_ingot'"));
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
