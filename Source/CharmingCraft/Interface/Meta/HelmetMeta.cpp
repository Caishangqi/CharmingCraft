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
}
