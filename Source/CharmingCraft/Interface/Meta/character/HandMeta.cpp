// Fill out your copyright notice in the Description page of Project Settings.


#include "HandMeta.h"

#include "CharmingCraft/Object/Structs/model/EquipmentComponentAnimation.h"

UHandMeta::UHandMeta()
{
	static ConstructorHelpers::FObjectFinder<UEquipmentComponentAnimation> EquipmentComponentAnimationFinder(
		TEXT(
			"EquipmentComponentAnimation'/Game/CharmingCraft/Assets/models/entity/Character/Animation/attack/punch/basic_punch_component_animation.basic_punch_component_animation'"));
	if (EquipmentComponentAnimationFinder.Succeeded())
	{
		LoadedAnimMontage = EquipmentComponentAnimationFinder.Object;
		UE_LOG(LogTemp, Warning,
		       TEXT("(+) UHandMeta::UHandMeta() AnimationDataAsset Loaded"))
		CurrentAttackStage = LoadedAnimMontage->AttackStageAnimations.Num();
	}
}
