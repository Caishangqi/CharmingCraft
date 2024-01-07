// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHandler.h"

#include "DamageChain.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"

void UDamageHandler::HandleDamage(FHitData HitData)
{
	if (!IsValid(NextHandler))
	{
		// At the end of the chain
		GetOuterAttributeComponent()->OnHitDataApply.Broadcast(HitData);
		// BrodCast the event to AttributeComponent allow UI to generate number
		UE_LOG(LogTemp, Warning, TEXT("[!] UDamageHandler::HandleDamage - END OF CHAIN"));
	}
}

void UDamageHandler::SetNextHandler(UDamageHandler* NewNextHandler)
{
	NextHandler = NewNextHandler;
}

UDAttributeComponent* UDamageHandler::GetOuterAttributeComponent()
{
	return Cast<UDamageChain>(GetOuter())->AttributeComponent.Get();
}
