// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActionComponent.h"

#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Skill/Actions/NativeAction.h"

UItemActionComponent::UItemActionComponent()
{
}

bool UItemActionComponent::SetActionSelected(UNativeAction* TargetAction)
{
	TArray<UNativeAction*> ActionWithSameType = GetActionByType(TargetAction->SkillType);
	for (UNativeAction* WithSameType : ActionWithSameType)
	{
		if (WithSameType == TargetAction)
		{
			TargetAction->SetIsSelected(true);
		}
		else
		{
			WithSameType->SetIsSelected(false);
		}
	}

	return true;
}

TArray<UNativeAction*> UItemActionComponent::GetActionByType(EItemDynamicSkillSlot ActionType)
{
	return *ActionInstanceMapping.Find(ActionType);
}

TArray<EItemDynamicSkillSlot> UItemActionComponent::GetTotalTypesActionInComponent()
{
	TArray<EItemDynamicSkillSlot> Keys;
	ActionInstanceMapping.GetKeys(Keys);
	return Keys;
}


void UItemActionComponent::CreateActionInstances()
{
	for (auto TemplateCollection : ActionTemplateCollection)
	{
		TObjectPtr<UNativeAction> ActionInstance = NewObject<UNativeAction>(this, TemplateCollection);
		ActionInstances.Add(ActionInstance);
		UE_LOG(LogChamingCraftAction, Display,
		       TEXT("		UItemActionComponent: 从模板中创建Action实例 <%s> 并添加到 ActionInstance"),
		       *ActionInstance->ActionName.ToString());

		// Mapping
		if (ActionInstanceMapping.Find(ActionInstance->SkillType))
		{
			ActionInstanceMapping.Find(ActionInstance->SkillType)->Add(ActionInstance);
		}
		else
		{
			TArray<UNativeAction*> SkillTypeArray;
			SkillTypeArray.Add(ActionInstance);
			ActionInstanceMapping.Add(ActionInstance->SkillType, SkillTypeArray);
		}
	}
}

void UItemActionComponent::PostInitProperties()
{
	Super::PostInitProperties();
	CreateActionInstances();
}

TArray<UNativeAction*> UItemActionComponent::GetActionInstances()
{
	return ActionInstances;
}

void UItemActionComponent::SetIsActive(bool RHS_bIsActive)
{
	Super::SetIsActive(RHS_bIsActive);
	// If is deactive, unbind all event related to this component

	// If is active bind all event related to this component
}

UItemStack * UItemActionComponent::GetOuterItemStack()
{
	return Cast<UItemStack>(GetOuter());
}
