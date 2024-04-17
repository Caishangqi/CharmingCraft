// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordMeta.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/fuller/EquipPartSwordFullerReinforced.h"

USwordMeta::USwordMeta()
{
	SetDefaultAssemble();
	// Default Animation
	static ConstructorHelpers::FObjectFinder<UEquipmentAnimation> EquipmentComponentAnimationFinder(
		TEXT(
			"EquipmentAnimation'/Game/CharmingCraft/Item/ItemEntityActor/Sword/Default_Sword_Attact_Animation.Default_Sword_Attact_Animation'"));
	if (EquipmentComponentAnimationFinder.Succeeded())
	{
		LoadedAnimMontage = EquipmentComponentAnimationFinder.Object;
		UE_LOG(LogTemp, Warning,
		       TEXT("(+) UEquipPartSwordBladeBasic::UEquipPartSwordBladeBasic() AnimationDataAsset Loaded"))
	}
	else
	{
		LoadedAnimMontage = nullptr;
	}
	// TODO: Disable until Refactor Sword Component
	/* 剑的攻击动画以剑的主要部件 Blade为准因此只用获取Blade上的动画 */
	//LoadedAnimMontage = SwordBlade->EquipmentAnimationDataAsset;

	CurrentAttackStage = LoadedAnimMontage->AttackStageAnimations.Num();
}

AItemEntityActor* USwordMeta::CreateItemEntityActor(const UObject* WorldContextObject, AActor * Owner)
{
	return Super::CreateItemEntityActor(WorldContextObject, Owner);

}

void USwordMeta::SetDefaultAssemble()
{
	/* Test Data */
	EquipmentAttribute.Damage = 10;
	EquipmentAttribute.AttackSpeed = 1.5;
	EquipmentAttribute.CriticalChance = 50;
	EquipmentAttribute.CriticalDamage = 150;
}
