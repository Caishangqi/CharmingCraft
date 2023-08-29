// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartHelmetCore.h"

#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"


UEquipPartHelmetCore::UEquipPartHelmetCore()
{
	TypeSuffix = "Helmet Core";
}

void UEquipPartHelmetCore::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	UEnum* MaterialEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMaterial"), true);
	FString MaterialString = MaterialEnum->GetNameStringByValue(static_cast<int64>(ComponentMaterial));

	FString Prefix, EnumValue;
	// 使用Split方法去除前缀
	MaterialString.Split(TEXT("::"), &Prefix, &EnumValue);

	const FDArmorMaterial* RowResult = ComponentMaterialDataTable.GetRow<FDArmorMaterial>(EnumValue);


	PartMesh = RowResult->CoreTexture;
}

void UEquipPartHelmetCore::OnRegister()
{
	Super::OnRegister();
	//UEquipPartHelmetCore::UpdateRenderMesh(ComponentMaterial);
}
