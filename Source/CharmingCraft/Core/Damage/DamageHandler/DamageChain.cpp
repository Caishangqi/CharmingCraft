// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageChain.h"
#include "PhysicalDamageHandler.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"

#define INITIALIZE_FIRST_HANDLER(HandlerType) \
FirstHandler = Cast<UDamageHandler>(CreateDamageHandler(EDamageHandlerType::HandlerType, this)); \
UDamageHandler* LastHandler = FirstHandler;

#define ADD_NEXT_HANDLER(HandlerType) \
if (LastHandler != nullptr) \
{ \
UDamageHandler* NextHandler = Cast<UDamageHandler>(CreateDamageHandler(EDamageHandlerType::HandlerType, this)); \
LastHandler->SetNextHandler(NextHandler); \
LastHandler = NextHandler; \
}


UDamageChain* UDamageChain::InitializeChain()
{
	AttributeComponent = Cast<UDAttributeComponent>(GetOuter());
	INITIALIZE_FIRST_HANDLER(Physical_Damage)
	// FirstHandler = NewObject<UPhysicalDamageHandler>(this, "PhysicalDamageHandler");
	// FirstHandler->SetNextHandler(NULL);
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

const TObjectPtr<UDamageHandler> UDamageChain::CreateDamageHandler(EDamageHandlerType HandlerType, UObject* Outer)
{
	switch (HandlerType)
	{
	case EDamageHandlerType::Physical_Damage:
		return NewObject<UPhysicalDamageHandler>(Outer, "PhysicalDamageHandler");
	default:
		return nullptr;
	}
}
