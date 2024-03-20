// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDynamicSkill.h"
#include "DAction.h"
#include "CharmingCraft/Core/Log/Logging.h"

UItemDynamicSkill::UItemDynamicSkill()
{
	/*
	GetDefaultObject()函数用于获取类的默认对象（Class Default Object, CDO）。
	CDO是每个类的一个特殊实例，代表该类的默认状态。CDO在类首次注册到UE4对象系统时创建
	，其目的是为新创建的对象实例提供默认值。因此，对于任何给定的类，CDO的构造器只会在该
	类首次加载到内存中时被调用一次，而不是每次调用GetDefaultObject()时
	*/

	// 如果在这里调用AddDynamicSkillToSlot,会被跳过因为这个时候类还没有实例化
	// 完毕,所以DynamicSkillsContent是空的,应该在PostInitProperties()中
	// 在进行初始化
}

void UItemDynamicSkill::PostInitProperties()
{
	Super::PostInitProperties();
	for (auto Skill : DynamicSkillsContent)
	{
		AddDynamicSkillToSlot(Skill);
	}
}

bool UItemDynamicSkill::AddDynamicSkillToSlot(TSubclassOf<UDAction> ActionClass)
{
	UE_LOG(LogChamingCraftAction, Display,
	       TEXT("[⚔️]  UItemDynamicSkill::AddDynamicSkillToSlot"));
	const TObjectPtr<UDAction> DefaultAction = NewObject<UDAction>(this, ActionClass);
	if (!DynamicSkills.Contains(DefaultAction))
	{
		DynamicSkills.Add(DefaultAction);
		return true;
	}
	return false;
}
