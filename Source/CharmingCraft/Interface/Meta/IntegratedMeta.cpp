// Fill out your copyright notice in the Description page of Project Settings.


#include "IntegratedMeta.h"
#include "CharmingCraft/Object/Structs/model/EquipmentComponentAnimation.h"

UIntegratedMeta::UIntegratedMeta()
{
	bIsRenderItem = true;
}

FAttackStageAnimation UIntegratedMeta::GetCurrentAttackAnimationMontage()
{
	return LoadedAnimMontage->AttackStageAnimations[CurrentAttackStage - 1];
}
