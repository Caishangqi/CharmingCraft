// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeItemAction.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Core/CraftComponent/ItemComponent/ItemActionComponent.h"

UNativeItemAction::UNativeItemAction()
{
}

bool UNativeItemAction::SetUpAttachment_Implementation(UObject* RHS_ParentObject)
{
	Super::SetUpAttachment_Implementation(RHS_ParentObject);
	// if the RHS_ParentObject is ItemActionComponent we get the ActionParentItemStack
	// for ItemAction logic needs
	if (RHS_ParentObject->IsA(UItemActionComponent::StaticClass()))
	{
		OuterItemActionComponent = Cast<UItemActionComponent>(RHS_ParentObject);
		ActionParentItemStack = OuterItemActionComponent->GetParentItemStack();
	}
	return true;
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
}
