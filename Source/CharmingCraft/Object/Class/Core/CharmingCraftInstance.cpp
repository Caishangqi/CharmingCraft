// Fill out your copyright notice in the Description page of Project Settings.


#include "CharmingCraftInstance.h"
#include "Engine/DataTable.h"

UCharmingCraftInstance::UCharmingCraftInstance()
{
	// Load the DataTable using its path
	static ConstructorHelpers::FObjectFinder<UDataTable> ArmorMaterialDataTableFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/Armor_Materials.Armor_Materials'"));
	if (ArmorMaterialDataTableFinder.Succeeded())
	{
		ArmorMaterialDataTable = ArmorMaterialDataTableFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MaterialMetaMapperFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'"));
	if (MaterialMetaMapperFinder.Succeeded())
	{
		MaterialMetaMapper = MaterialMetaMapperFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> BladeBasicMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/blade/BladeBasicMaterial.BladeBasicMaterial'"));
	if (BladeBasicMaterialFinder.Succeeded())
	{
		BladeBasicMaterial = BladeBasicMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> FullerReinforcedMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/fuller/FullerReinforcedMaterial.FullerReinforcedMaterial'"));
	if (FullerReinforcedMaterialFinder.Succeeded())
	{
		FullerReinforcedMaterial = FullerReinforcedMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> GuardMakeShiftMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/guard/GuardMakeShiftMaterial.GuardMakeShiftMaterial'"));
	if (GuardMakeShiftMaterialFinder.Succeeded())
	{
		GuardMakeShiftMaterial = GuardMakeShiftMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> HiltBasicMaterialFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/hilt/HiltBasicMaterial.HiltBasicMaterial'"));
	if (HiltBasicMaterialFinder.Succeeded())
	{
		HiltBasicMaterial = HiltBasicMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> PommelDecorativeMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/pommel/PommelDecorativeMaterial.PommelDecorativeMaterial'"));
	if (PommelDecorativeMaterialFinder.Succeeded())
	{
		PommelDecorativeMaterial = PommelDecorativeMaterialFinder.Object;
	}
}
