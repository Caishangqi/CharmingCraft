// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeItemAction.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "../Core/CharmingCraftInstance.h"

UNativeItemAction::UNativeItemAction()
{
}

void UNativeItemAction::StartAction_Implementation(APawn* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	CastInstigatorPlayer = Cast<ANativePlayerCharacter>(CachedInstigator);
	GameInstance = Cast<UCharmingCraftInstance>(Instigator->GetGameInstance());
}
