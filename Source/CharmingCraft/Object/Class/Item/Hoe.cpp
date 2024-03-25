// Fill out your copyright notice in the Description page of Project Settings.


#include "Hoe.h"

#include "CharmingCraft/Core/Builds/Module/BuildModuleManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "../Core/Item/Meta/Abstruct/IntegratedMeta.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

UHoe::UHoe()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Hoe");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::HOE;
	ItemMetaClass = UIntegratedMeta::StaticClass();
	Socket = EEquipmentSocket::HAND;
	DescribeText = FText::FromString(
		"A long-handled gardening tool with a thin metal blade, used mainly for weeding and breaking up soil.");

	// /Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Hoe/Hoe.Hoe'

	static ConstructorHelpers::FObjectFinder<UBlueprint> ActorBlueprint(
		TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Hoe/Hoe.Hoe'"));
	if (ActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultItemEntityActorClass = ActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
	// Load the Build model
	static ConstructorHelpers::FObjectFinder<UBlueprint> BuildModelBlueprint(
		TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Block/Module/BuildModel/BuildModel_Hoe.BuildModel_Hoe'"));
	if (ActorBlueprint.Succeeded())
	{
		BuildModel = BuildModelBlueprint.Object->GeneratedClass;
	}
	// Default ItemDynamicSkill
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemDynamicSkillFinder(
		TEXT(
			"Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Hoe/IDS_Hoe.IDS_Hoe'"));
	if (ItemDynamicSkillFinder.Succeeded())
	{
		ItemDynamicSkillClass = ItemDynamicSkillFinder.Object->GeneratedClass;
	}
}

/*
 *	Note: Hoe Interact event move to HoeBuildModel, include FrameActor and some validation Check
 */

void UHoe::OnEquip(UObject* Instigator, UItemStack* OnEquipItem)
{
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Item Internal Class OnEquip() Class Name=		%s"),
	       *this->GetName());

	// Call BuildModuleManager start the HoeBuildModel to display specific Frame Actor
	// Add BuildModel to the CurrentLoadedBuildModels
	Cast<UCharmingCraftInstance>(Instigator->GetWorld()->GetGameInstance())->BuildModuleManager->StartCustomModel(
		Instigator, BuildModel);

	Super::OnEquip(Instigator, OnEquipItem);
}

void UHoe::UnEquip(UObject* Instigator, UItemStack* UnEquipItem)
{
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Item Internal Class UnEquip() Class Name=		%s"),
	       *this->GetName());
	// Call BuildModuleManager tell the HoeBuildModel to remove specific Frame Actor
	// Remove BuildModel from the CurrentLoadedBuildModels
	Cast<UCharmingCraftInstance>(Instigator->GetWorld()->GetGameInstance())->BuildModuleManager->StopCustomModel(
		Instigator, BuildModel);
	Super::UnEquip(Instigator, UnEquipItem);
}
