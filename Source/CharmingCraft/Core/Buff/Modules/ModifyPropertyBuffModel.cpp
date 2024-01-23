// Fill out your copyright notice in the Description page of Project Settings.


#include "ModifyPropertyBuffModel.h"

#include "DCharacter.h"
#include "CharmingCraft/Core/Buff/BuffInfo.h"


void UModifyPropertyBuffModel::Apply_Implementation(UBuffInfo* BuffInfo, FHitData& HitData)
{
	Super::Apply_Implementation(BuffInfo, HitData);
	AttributeComponent = Cast<UDAttributeComponent>(
		BuffInfo->Target->GetComponentByClass(UDAttributeComponent::StaticClass()));
	if (AttributeComponent)
	{
		/* TODO: Consider use operate override &= */
		AttributeComponent->AttackRange += PlayerAttributeDelta.AttackRange;
		AttributeComponent->Health += PlayerAttributeDelta.Health;
		AttributeComponent->Damage += PlayerAttributeDelta.Damage;
		AttributeComponent->HealthMax += PlayerAttributeDelta.HealthMax;
		AttributeComponent->AbilityPower += PlayerAttributeDelta.AbilityPower;
		AttributeComponent->Mana += PlayerAttributeDelta.Mana;
		AttributeComponent->CurrentLevelXP += PlayerAttributeDelta.CurrentLevelXP;
		AttributeComponent->Armour += PlayerAttributeDelta.Armour;
		AttributeComponent->MagicDefense += PlayerAttributeDelta.MagicDefense;
		AttributeComponent->KnockBackResistance += PlayerAttributeDelta.KnockBackResistance;
		AttributeComponent->CriticalChance += PlayerAttributeDelta.CriticalChance;
		AttributeComponent->CriticalDamageEnhance += PlayerAttributeDelta.CriticalDamageEnhance;
		AttributeComponent->CriticalDamageDefenseEnhance += PlayerAttributeDelta.CriticalDamageDefenseEnhance;
		AttributeComponent->AttackSpeedEnhance += PlayerAttributeDelta.AttackSpeedEnhance;
		AttributeComponent->InteractRange += PlayerAttributeDelta.InteractRange;
	}
}
