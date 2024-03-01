// Fill out your copyright notice in the Description page of Project Settings.
#include "../Object/Components/Container/WorkBenchComponent.h"

#include "CharmingCraft/Core/Container/Lib/ItemEntityUtilityLibrary.h"
#include "CharmingCraft/Interface/EquipPartComponent.h"
#include "CharmingCraft/Interface/Meta/IntegratedMeta.h"

UWorkBenchComponent::UWorkBenchComponent()
{
	InventorySize = 2;
}

void UWorkBenchComponent::PostInitProperties()
{
	Super::PostInitProperties();
	Inventory.SetNum(2);
}

void UWorkBenchComponent::BeginPlay()
{
	Super::BeginPlay();
	// 设置背包大小
	Inventory.SetNum(2);
	Inventory[0] = nullptr;
	Inventory[1] = nullptr;
}

void UWorkBenchComponent::OnRegister()
{
	Super::OnRegister();
}

bool UWorkBenchComponent::SetPartMaterial(UEquipPartComponent* Component, EMaterial Material)
{
	UE_LOG(LogTemp, Warning, TEXT(
		       "Start Manipulate"
	       ))
	UE_LOG(LogTemp, Warning, TEXT(
		       "Manipulate Information: %s"
	       ), *Component->GetOuter()->GetName())
	UE_LOG(LogTemp, Warning, TEXT(
		       "Manipulate Information: %s"
	       ), *Component->GetClass()->GetName())

	Component->ComponentMaterial = Material;
	Component->UpdateRenderMesh(Component->ComponentMaterial);

	UE_LOG(LogTemp, Warning, TEXT(
		       "Manipulate Information: %hhd"
	       ), Component->ComponentMaterial)

	UItemMeta* Meta = Cast<UItemMeta>(Component->GetOuter());
	UItemEntityUtilityLibrary::UpdateMeshMaterialSlot(Meta->ItemModelMesh,
	                                                  Component->MaterialSlotIndex, Component->PartMaterial);
	UE_LOG(LogTemp, Warning, TEXT(
		       "Manipulate Information: %hhd"
	       ), Meta->bIsRenderItem);
	// TODO: Temporally Disable
	//Meta->UpdateRender(GetWorld());

	return true;
}
