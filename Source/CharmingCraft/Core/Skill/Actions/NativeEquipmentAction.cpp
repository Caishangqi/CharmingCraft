// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeEquipmentAction.h"

#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/RenderActor/Abstract/EquipmentEntityActor.h"

UNativeEquipmentAction::UNativeEquipmentAction()
{
	
}

void UNativeEquipmentAction::StartAction_Implementation(APawn* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ItemEntityActor = Cast<AEquipmentEntityActor>(BindItemStack->ItemMeta->ItemEntityActor);
}
