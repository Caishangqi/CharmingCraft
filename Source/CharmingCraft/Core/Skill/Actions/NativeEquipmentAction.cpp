// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeEquipmentAction.h"

#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/RenderActor/Abstract/EquipmentEntityActor.h"
#include "CharmingCraft/Core/Skill/Lib/ActionCastLib.h"

UNativeEquipmentAction::UNativeEquipmentAction()
{
	
}

FActionActorData UNativeEquipmentAction::GetActionActorData_Implementation()
{
	FActionActorData ActionActorData = Super::GetActionActorData_Implementation();
	ActionActorData.ActionHitData = GetActionHitData(); // Get HitData
	ActionActorData.Parent = this;
	ActionActorData.InstigatorAction = this;
	ActionActorData.ActionActorOwner = CastInstigatorPlayer;
	// Add Callback to ActionActor
	ActionActorData.OnHitCastAction = UActionCastLib::GetItemActionsByType(BindItemStack,CastInstigatorPlayer,EItemDynamicSkillSlot::ON_HIT);
	if (ActionActorData.OnHitCastAction)
	{
		ActionActorData.OnHitCastAction->IgnoreTargetActors.Append(this->IgnoreTargetActors);
	}
	return ActionActorData;
}

void UNativeEquipmentAction::StartAction_Implementation(APawn* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ItemEntityActor = Cast<AEquipmentEntityActor>(BindItemStack->ItemMeta->ItemEntityActor);
}
