// Fill out your copyright notice in the Description page of Project Settings.


#include "Hoe.h"

#include "CharmingCraft/Interface/Meta/IntegratedMeta.h"

UHoe::UHoe()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Hoe");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::HOE;
	ItemMetaClass = UIntegratedMeta::StaticClass();
	Socket = EEquipmentSocket::HAND;
	DescribeText = FText::FromString("A long-handled gardening tool with a thin metal blade, used mainly for weeding and breaking up soil.");
	
	// /Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Hoe/Hoe.Hoe'
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> ActorBlueprint(TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Hoe/Hoe.Hoe'"));
	if (ActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultItemEntityActorClass = ActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
}

