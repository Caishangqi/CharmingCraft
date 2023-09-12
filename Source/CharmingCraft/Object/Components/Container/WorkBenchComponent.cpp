// Fill out your copyright notice in the Description page of Project Settings.

#include "CharmingCraft/Interface/EquipPartComponent.h"
#include "../Object/Components/Container/WorkBenchComponent.h"

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
	return true;
}
