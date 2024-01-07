// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageChain.h"

#include "PhysicalDamageHandler.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"

UDamageChain* UDamageChain::InitializeChain()
{
	
	AttributeComponent = Cast<UDAttributeComponent>(GetOuter());
	FirstHandler = NewObject<UPhysicalDamageHandler>(this, "PhysicalDamageHandler");
	FirstHandler->SetNextHandler(NULL);
	return this;
}

void UDamageChain::HandleDamage(FHitData HitData)
{
	if (!AttributeComponent)
	{
		UE_LOG(LogTemp, Error,
		       TEXT(
			       "[!] UDamageChain::HandleDamage - AttributeComponent is null, perhaps you do not initialize the chain"
		       ));
	}
	FirstHandler->HandleDamage(HitData);
}
