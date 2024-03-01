// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordMeta.h"

#include "CharmingCraft/Core/Item/RenderActor/Equipment/SwordEntityActorP5.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/blade/EquipPartSwordBladeBasic.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/fuller/EquipPartSwordFullerReinforced.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/guard/EquipPartSwordGuardMakeShift.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/hilt/EquipPartSwordHiltBasic.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/pommel/EquipPartSwordPommelDecorative.h"

USwordMeta::USwordMeta()
{
	SetDefaultAssemble();
	ItemEntityActorClass = ASwordEntityActorP5::StaticClass();
	/* 剑的攻击动画以剑的主要部件 Blade为准因此只用获取Blade上的动画 */
	LoadedAnimMontage = SwordBlade->EquipmentComponentAnimationDataAsset;
	CurrentAttackStage = SwordBlade->EquipmentComponentAnimationDataAsset->AttackStageAnimations.Num();
}

AItemEntityActor* USwordMeta::CreateItemEntityActor(const UObject* WorldContextObject)
{
	
	ASwordEntityActorP5* SwordActor = Cast<ASwordEntityActorP5>(Super::CreateItemEntityActor(WorldContextObject));
	if (SwordActor)
	{
		SwordActor->Blade->SetStaticMesh(SwordBlade->PartMesh);
		SwordActor->Fuller->SetStaticMesh(SwordFuller->PartMesh);
		SwordActor->Guard->SetStaticMesh(SwordGuard->PartMesh);
		SwordActor->Hilt->SetStaticMesh(SwordHilt->PartMesh);
		SwordActor->Pommel->SetStaticMesh(SwordPommel->PartMesh);
		return SwordActor;
	}
	else
	{
		return Super::CreateItemEntityActor(WorldContextObject);
	}
	
}

void USwordMeta::SetDefaultAssemble()
{
	SwordBlade = CreateDefaultSubobject<UEquipPartSwordBladeBasic>("Blade Basic");
	SwordFuller = CreateDefaultSubobject<UEquipPartSwordFullerReinforced>("Fuller Reinforced");
	SwordGuard = CreateDefaultSubobject<UEquipPartSwordGuardMakeShift>("Guard MakeShift");
	SwordHilt = CreateDefaultSubobject<UEquipPartSwordHiltBasic>("Hilt Basic");
	SwordPommel = CreateDefaultSubobject<UEquipPartSwordPommelDecorative>("Pommel Decorative");
	/* Test Data */
	EquipmentAttribute.Damage = 10;
	EquipmentAttribute.AttackSpeed = 1.5;
	EquipmentAttribute.CriticalChance = 50;
	EquipmentAttribute.CriticalDamage = 150;
}
