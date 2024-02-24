// Fill out your copyright notice in the Description page of Project Settings.


#include "Lead.h"

ULead::ULead()
{
	DisplayName = FText::FromString("Lead");
	MaxStackSize = 64;
	ItemType = EItemType::MATERIAL;
	DescribeText = FText::FromString("It is a heavy metal that is denser than most common materials.");
	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(
		TEXT("/Script/Engine.Texture2D'/Game/CharmingCraft/Assets/textures/item/lead_ingot.lead_ingot'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTexture(
		TEXT("/Script/Engine.StaticMesh'/Game/CharmingCraft/Assets/models/item/lead_ingot.lead_ingot'"));
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
