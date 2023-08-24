// Fill out your copyright notice in the Description page of Project Settings.


#include "HelmetClass.h"

#include "CharmingCraft/Object/Components/EquipPart/EquipPartArmorPlates.h"
#include "CharmingCraft/Object/Components/EquipPart/EquipPartArmorTrim.h"
#include "CharmingCraft/Object/Components/EquipPart/EquipPartHelmetCore.h"

UHelmetClass::UHelmetClass()
{
	HelmetCore = CreateDefaultSubobject<UEquipPartHelmetCore>("HelmetCore");
	EquipPartArmorPlates = CreateDefaultSubobject<UEquipPartArmorPlates>("ArmorPlates");
	EquipPartArmorTrim = CreateDefaultSubobject<UEquipPartArmorTrim>("ArmorTrim");
}
