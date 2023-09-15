// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorPlates.h"

#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"


UEquipPartArmorPlates::UEquipPartArmorPlates()
{
	TypeSuffix = "Armor Plates";
	TypeSuffixShort = "Plates";
	Description = "Armor Plates is Armor Plates so it should be Armor Plates or you can also call it Armor Plates";
	ItemNeedToForge = 4;
}

void UEquipPartArmorPlates::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	//UEnum* MaterialEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("/Script/CharmingCraft.EMaterial"), true);

	UEnum* MaterialEnum = FindObject<UEnum>(this, TEXT("EMaterial"), true);
	FString MaterialString = MaterialEnum->GetNameStringByValue(static_cast<int64>(ComponentMaterial));

	FString Prefix, EnumValue;
	// 使用Split方法去除前缀
	MaterialString.Split(TEXT("::"), &Prefix, &EnumValue);

	const FDArmorMaterial* RowResult = ComponentMaterialDataTable.GetRow<FDArmorMaterial>(EnumValue);


	PartMesh = RowResult->PlateTexture;
}

void UEquipPartArmorPlates::OnRegister()
{
	Super::OnRegister();
	//UEquipPartArmorPlates::UpdateRenderMesh(ComponentMaterial);
}
