// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordMeta.h"

#include "CharmingCraft/Object/Components/EquipPart/model/sword/blade/EquipPartSwordBladeBasic.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/fuller/EquipPartSwordFullerReinforced.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/guard/EquipPartSwordGuardMakeShift.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/hilt/EquipPartSwordHiltBasic.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/pommel/EquipPartSwordPommelDecorative.h"

USwordMeta::USwordMeta()
{
	SetDefaultAssemble();

	
}

void USwordMeta::SetDefaultAssemble()
{
	SwordBlade = CreateDefaultSubobject<UEquipPartSwordBladeBasic>("Blade Basic");
	SwordFuller = CreateDefaultSubobject<UEquipPartSwordFullerReinforced>("Fuller Reinforced");
	SwordGuard = CreateDefaultSubobject<UEquipPartSwordGuardMakeShift>("Guard MakeShift");
	SwordHilt = CreateDefaultSubobject<UEquipPartSwordHiltBasic>("Hilt Basic");
	SwordPommel = CreateDefaultSubobject<UEquipPartSwordPommelDecorative>("Pommel Decorative");
}
