// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalDamageHandler.h"

#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"

void UPhysicalDamageHandler::HandleDamage(FHitData HitData)
{
	if (HitData.Damage <= 0.0f)
	{
		NextHandler->HandleDamage(HitData);
	}
	else
	{
		/* Critical Damage Calculation */
		HitData.CriticalDamage = URoguelikeAttributeLibrary::GetCriticalDamage(
			HitData.CriticalDamage, GetOuterAttributeComponent()->CriticalDamageDefenseEnhance);

		/* True Damage Handle After Armour Damage reduced */
		HitData.Damage = URoguelikeAttributeLibrary::GetDamage(HitData.Damage, GetOuterAttributeComponent()->Armour,
		                                                       HitData.IsCritic,
		                                                       HitData.CriticalDamage);
		UE_LOG(LogTemp, Warning, TEXT("[!] UDamageHandler::HandleDamage Data: %d %f"), HitData.CriticalDamage,
		       HitData.Damage);
		ApplyDataToAttribute(-HitData.Damage);
	}
	Super::HandleDamage(HitData);
}

void UPhysicalDamageHandler::ApplyDataToAttribute(const float Data)
{
	GetOuterAttributeComponent()->ApplyHealthChange(Data);
}
