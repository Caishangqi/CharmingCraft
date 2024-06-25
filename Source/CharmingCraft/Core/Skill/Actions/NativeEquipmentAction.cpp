// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeEquipmentAction.h"

#include "CharmingCraft/Core/CraftComponent/ItemComponent/ItemActionComponent.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/RenderActor/Abstract/EquipmentEntityActor.h"
#include "CharmingCraft/Core/Skill/Lib/ActionCastLib.h"

UNativeEquipmentAction::UNativeEquipmentAction()
{
}

FActionActorData UNativeEquipmentAction::GetActionActorData_Implementation()
{
	FActionActorData ActionActorData = Super::GetActionActorData_Implementation();
	ActionActorData.WorldContextObject = CastInstigatorPlayer;
	ActionActorData.ActionHitData = GetActionHitData(); // Get HitData
	ActionActorData.Parent = this;
	ActionActorData.InstigatorAction = this;
	ActionActorData.ActionActorOwner = CastInstigatorPlayer;

	/*
	 * 这里给EquipAction的技能实体绑定命中时的技能,可以从NativeAction的所属技能组件中拿取
	 */
	for (UNativeAction* ActionByType : OuterItemActionComponent->GetActionByType(EItemDynamicSkillSlot::ON_HIT))
	{
		if (ActionByType->GetIsSelected())
		{
			// UActionCastLib::GetItemActionsByType(ActionParentItemStack,CastInstigatorPlayer,EItemDynamicSkillSlot::ON_HIT);
			ActionActorData.OnHitCastAction = ActionByType;
		}
	}

	// 这里防止技能实体和自己进行碰撞反应
	if (ActionActorData.OnHitCastAction)
	{
		ActionActorData.OnHitCastAction->IgnoreTargetActors.Append(this->IgnoreTargetActors);
	}
	
	return ActionActorData;
}

void UNativeEquipmentAction::StartAction_Implementation(APawn* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ItemEntityActor = Cast<AEquipmentEntityActor>(ActionParentItemStack->ItemMeta->ItemEntityActor);
}
