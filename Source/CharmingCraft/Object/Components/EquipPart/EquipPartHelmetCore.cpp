// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartHelmetCore.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"


UEquipPartHelmetCore::UEquipPartHelmetCore()
{
	TypeSuffix = "Helmet Core";
	TypeSuffixShort = "Core";
	Description = "Helmet Core is Helmet Core so it should be Helmet Core or you can also call it Helmet Core";
	ItemNeedToForge = 2;
	MaterialSlotIndex = 0;
}

void UEquipPartHelmetCore::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	Super::UpdateRenderMesh(NewComponentMaterialText);
	PartMaterial = FoundRow->CoreTexture;
}

void UEquipPartHelmetCore::OnRegister()
{
	Super::OnRegister();
}

void UEquipPartHelmetCore::BeginPlay()
{
	Super::BeginPlay();
	UEquipPartHelmetCore::UpdateRenderMesh(ComponentMaterial);
}
