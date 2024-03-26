// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "CharmingCraft/Core/Item/Meta/Abstruct/IntegratedMeta.h"

UBow::UBow()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Bow");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::BOW;
	ItemMetaClass = UIntegratedMeta::StaticClass();
	Socket = EEquipmentSocket::HAND;
	OrthoWidth = 192;
	DescribeText = FText::FromString(
		"a weapon for shooting arrows, typically made of a curved piece of wood whose ends are joined by a taut string.");
	static ConstructorHelpers::FObjectFinder<UBlueprint> ActorBlueprint(
		TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Bow/Bow.Bow'"));
	if (ActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultItemEntityActorClass = ActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
}
