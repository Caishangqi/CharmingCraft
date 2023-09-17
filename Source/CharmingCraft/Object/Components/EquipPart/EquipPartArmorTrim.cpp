// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorTrim.h"
#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"

UEquipPartArmorTrim::UEquipPartArmorTrim()
{
	TypeSuffix = "Armor Trim";
	TypeSuffixShort = "Trim";
	Description = "Armor Trim is Armor Trim so it should be Armor Trim or you can also call it Armor Trim";
	ItemNeedToForge = 3;
	MaterialSlotIndex = 2;
}


void UEquipPartArmorTrim::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	Super::UpdateRenderMesh(NewComponentMaterialText);
	PartMaterial = FoundRow->TrimTexture;
}

void UEquipPartArmorTrim::OnRegister()
{
	Super::OnRegister();
}

void UEquipPartArmorTrim::BeginPlay()
{
	Super::BeginPlay();
	UEquipPartArmorTrim::UpdateRenderMesh(ComponentMaterial);
}
