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

bool UItemActionComponent::AddActionToComponent(UNativeAction* TargetAction)
{
	TargetAction->SetUpAttachment(this);
	ActionInstances.Add(TargetAction);
	MappingActionContent(TargetAction);
	return true;
}


void UItemActionComponent::CreateActionInstances()
{
	for (auto TemplateCollection : ActionTemplateCollection)
	{
		TObjectPtr<UNativeAction> ActionInstance = NewObject<UNativeAction>(this, TemplateCollection);
		ActionInstance->SetUpAttachment(this);
		ActionInstances.Add(ActionInstance);
		UE_LOG(LogChamingCraftAction, Display,
		       TEXT("		UItemActionComponent: 从模板中创建Action实例 <%s> 并添加到 ActionInstance"),
		       *ActionInstance->ActionName.ToString());
		MappingActionContent(ActionInstance);
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

UItemStack* UItemActionComponent::GetParentItemStack()
{
	if (GetParentAttachedObject())
	{
		return Cast<UItemStack>(GetParentAttachedObject());
	}
	else if (GetOuter()->IsA(UItemStack::StaticClass()))
	{
		return Cast<UItemStack>(GetOuter());
	}
	else
	{
		UE_LOG(LogChamingCraftAction, Error,
		       TEXT("[⚔️]  未能找到物品技能组件所属的ItemStack\n"
			       "		可能是由未正确 SetUpAttachment所导致"));
		throw std::invalid_argument("ParentAttachedObject is null");
	}
}

void UItemActionComponent::MappingActionContent(UNativeAction* TargetAction)
{
	// Mapping
	if (ActionInstanceMapping.Find(TargetAction->SkillType))
	{
		ActionInstanceMapping.Find(TargetAction->SkillType)->Add(TargetAction);
	}
	else
	{
		TArray<UNativeAction*> SkillTypeArray;
		SkillTypeArray.Add(TargetAction);
		ActionInstanceMapping.Add(TargetAction->SkillType, SkillTypeArray);
	}
}
