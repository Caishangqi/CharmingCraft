// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeItemAction.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Core/CraftComponent/ItemComponent/ItemActionComponent.h"

UNativeItemAction::UNativeItemAction()
{
}

void UNativeItemAction::PostInitProperties()
{
	Super::PostInitProperties();
	
}

void UNativeItemAction::StartAction_Implementation(APawn* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	CastInstigatorPlayer = Cast<ANativePlayerCharacter>(CachedInstigator);
	GameInstance = Cast<UCharmingCraftInstance>(Instigator->GetGameInstance());
	OuterItemActionComponent = Cast<UItemActionComponent>(GetOuter());
	ActionParentItemStack = OuterItemActionComponent->GetOuterItemStack();
}
