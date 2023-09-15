// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorTrim.h"

#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"

UEquipPartArmorTrim::UEquipPartArmorTrim()
{
	TypeSuffix = "Armor Trim";
	TypeSuffixShort = "Trim";
	Description = "Armor Trim is Armor Trim so it should be Armor Trim or you can also call it Armor Trim";
	ItemNeedToForge = 3;
}


void UEquipPartArmorTrim::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	UEnum* MaterialEnum = FindObject<UEnum>(this, TEXT("EMaterial"), true);
	FString MaterialString = MaterialEnum->GetNameStringByValue(static_cast<int64>(ComponentMaterial));

	FString Prefix, EnumValue;
	// 使用Split方法去除前缀
	MaterialString.Split(TEXT("::"), &Prefix, &EnumValue);

	const FDArmorMaterial* RowResult = ComponentMaterialDataTable.GetRow<FDArmorMaterial>(EnumValue);


	PartMesh = RowResult->TrimTexture;
}

void UEquipPartArmorTrim::OnRegister()
{
	Super::OnRegister();
	//UEquipPartArmorTrim::UpdateRenderMesh(ComponentMaterial);
}
