// Fill out your copyright notice in the Description page of Project Settings.


#include "CharmingCraftInstance.h"
#include "Engine/DataTable.h"

UCharmingCraftInstance::UCharmingCraftInstance()
{
	// Load the DataTable using its path
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/Armor_Materials.Armor_Materials'"));
	if (DataTableFinder.Succeeded())
	{
		ArmorMaterialDataTable = DataTableFinder.Object;
	}
}
