// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorTrim.h"

UEquipPartArmorTrim::UEquipPartArmorTrim()
{
	TypeSuffix = "Armor Trim";
	UEquipPartArmorTrim::UpdateRenderMesh(ComponentMaterialText);
}

void UEquipPartArmorTrim::UpdateRenderMesh(FString& NewComponentMaterialText)
{
	if (Super::UpdateRenderMesh(NewComponentMaterialText);
		const FDArmorMaterial* RowResult = ComponentMaterial.GetRow<FDArmorMaterial>(NewComponentMaterialText))
	{
		PartMesh = RowResult->TrimTexture;
	}
}
