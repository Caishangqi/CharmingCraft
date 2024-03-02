// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickaxe.h"
#include "CharmingCraft/Interface/Meta/IntegratedMeta.h"

UPickaxe::UPickaxe()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Pickaxe");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::PICKAXE;
	ItemMetaClass = UIntegratedMeta::StaticClass();
	Socket = EEquipmentSocket::HAND;
	DescribeText = FText::FromString("A pickaxe, pick-axe, or pick is a generally T-shaped hand tool used for prying.");
	// /Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Pickaxe/Pickaxe.Pickaxe'
	static ConstructorHelpers::FObjectFinder<UBlueprint> ActorBlueprint(TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Pickaxe/Pickaxe.Pickaxe'"));
	if (ActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultItemEntityActorClass = ActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
	
}
