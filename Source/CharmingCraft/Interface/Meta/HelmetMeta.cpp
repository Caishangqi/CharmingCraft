// Fill out your copyright notice in the Description page of Project Settings.


#include "HelmetMeta.h"
#include "../Object/Components/EquipPart/EquipPartArmorPlates.h"
#include "../Object/Components/EquipPart/EquipPartArmorTrim.h"
#include "../Object/Components/EquipPart/EquipPartHelmetCore.h"

UHelmetMeta::UHelmetMeta()
{
	HelmetCore = CreateDefaultSubobject<UEquipPartHelmetCore>("HelmetCore");
	EquipPartArmorPlates = CreateDefaultSubobject<UEquipPartArmorPlates>("ArmorPlates");
	EquipPartArmorTrim = CreateDefaultSubobject<UEquipPartArmorTrim>("ArmorTrim");


	// 设置Static Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
		TEXT(
			"/Script/Engine.StaticMesh'/Game/CharmingCraft/Assets/models/armor/helmet/Minecraft_Intergrate_Armor_Helmet.Minecraft_Intergrate_Armor_Helmet'"));
	if (MeshAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Static Mesh Founded!"));
		ItemModelMesh = MeshAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Static Mesh Can not Found"));
	}

	bIsRenderItem = true;
}

void UHelmetMeta::PostInitProperties()
{
	Super::PostInitProperties();
}
