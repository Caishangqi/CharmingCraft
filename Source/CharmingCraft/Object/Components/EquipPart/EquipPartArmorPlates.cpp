// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorPlates.h"


UEquipPartArmorPlates::UEquipPartArmorPlates()
{
	TypeSuffix = "Armor Plates";
	UEquipPartArmorPlates::UpdateRenderMesh(ComponentMaterialText);
}

void UEquipPartArmorPlates::UpdateRenderMesh(FString& NewComponentMaterialText)
{
	if (Super::UpdateRenderMesh(NewComponentMaterialText);
		const FDArmorMaterial* RowResult = ComponentMaterial.GetRow<FDArmorMaterial>(NewComponentMaterialText))
	{
		PartMesh = RowResult->PlateTexture;
	}
}
