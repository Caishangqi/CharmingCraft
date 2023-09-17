// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorPlates.h"

#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"


UEquipPartArmorPlates::UEquipPartArmorPlates()
{
	TypeSuffix = "Armor Plates";
	TypeSuffixShort = "Plates";
	Description = "Armor Plates is Armor Plates so it should be Armor Plates or you can also call it Armor Plates";
	ItemNeedToForge = 4;
	MaterialSlotIndex = 1;
}

void UEquipPartArmorPlates::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	Super::UpdateRenderMesh(NewComponentMaterialText);
	PartMaterial = FoundRow->PlateTexture;
}

void UEquipPartArmorPlates::OnRegister()
{
	Super::OnRegister();
}

void UEquipPartArmorPlates::BeginPlay()
{
	Super::BeginPlay();
	UEquipPartArmorPlates::UpdateRenderMesh(ComponentMaterial);
}
