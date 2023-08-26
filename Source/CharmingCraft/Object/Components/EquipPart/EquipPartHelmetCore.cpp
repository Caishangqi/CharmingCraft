// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartHelmetCore.h"


UEquipPartHelmetCore::UEquipPartHelmetCore()
{
	TypeSuffix = "Helmet Core";
	UEquipPartHelmetCore::UpdateRenderMesh(ComponentMaterialText);
}

void UEquipPartHelmetCore::UpdateRenderMesh(FString& NewComponentMaterialText)
{
	if (Super::UpdateRenderMesh(NewComponentMaterialText);
		const FDArmorMaterial* RowResult = ComponentMaterial.GetRow<FDArmorMaterial>(NewComponentMaterialText))
	{
		PartMesh = RowResult->CoreTexture;
	}
}
