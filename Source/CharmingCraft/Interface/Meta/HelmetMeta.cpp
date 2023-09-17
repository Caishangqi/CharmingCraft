// Fill out your copyright notice in the Description page of Project Settings.


#include "HelmetMeta.h"
#include "../Object/Components/EquipPart/EquipPartArmorPlates.h"
#include "../Object/Components/EquipPart/EquipPartArmorTrim.h"
#include "../Object/Components/EquipPart/EquipPartHelmetCore.h"
#include "Blueprint/UserWidget.h"

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
		UStaticMesh* RenderMaterial = DuplicateObject<UStaticMesh>(
			MeshAsset.Object, this);

		ItemModelMesh = RenderMaterial;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Static Mesh Can not Found"));
	}

	bIsRenderItem = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT(
		"/Script/UMGEditor.WidgetBlueprint'/Game/CharmingCraft/UI/Container/WorkBench/LayOut/W_WorkBench_LayOut_Helmet.W_WorkBench_LayOut_Helmet_C'"));
	if (WidgetClassFinder.Succeeded())
	{
		Layout = WidgetClassFinder.Class;
	}
}

void UHelmetMeta::PostInitProperties()
{
	Super::PostInitProperties();
}
