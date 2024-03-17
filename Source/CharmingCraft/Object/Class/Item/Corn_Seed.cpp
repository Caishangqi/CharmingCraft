// Fill out your copyright notice in the Description page of Project Settings.


#include "Corn_Seed.h"

#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"

UCorn_Seed::UCorn_Seed()
{
	DisplayName = FText::FromString("Corn seeds");
	MaxStackSize = 64;
	ItemType = EItemType::SEEDS;
	Material = EMaterial::CORN_SEED;
	AssetName = TEXT("corn_seed");
	ItemMetaClass = UItemMeta::StaticClass();
	DescribeText = FText::FromString("One of the most popular grains. The sweet, fresh cobs are a summer favorite.");
	Super::LoadLocalAsset();

	// Load the Build model
	static ConstructorHelpers::FObjectFinder<UBlueprint> BuildModelBlueprint(
		TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Block/Module/BuildModel/BuildModel_Seeds.BuildModel_Seeds'"));
	if (BuildModelBlueprint.Succeeded())
	{
		BuildModel = BuildModelBlueprint.Object->GeneratedClass;
	}
	// Load the crop entity
	static ConstructorHelpers::FObjectFinder<UBlueprint> CropEntityActorBlueprint(
		TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Resource/Crops/Corn/Crop_Corn.Crop_Corn'"));
	if (BuildModelBlueprint.Succeeded())
	{
		CropEntityClass = CropEntityActorBlueprint.Object->GeneratedClass;
	}
}

void UCorn_Seed::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator)
{
	Super::OnItemInteract(InteractItemStack, Instigator);
}
