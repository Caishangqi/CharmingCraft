// Fill out your copyright notice in the Description page of Project Settings.
#include "Sword.h"
#include "DCharacter.h"
#include "../Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Core/Item/RenderActor/Equipment/SwordEntityActorP5.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Interface/Meta/model/SwordMeta.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"
#include "Components/ArrowComponent.h"

/* 不修改数据, 只读取和执行操作 原型物品模板类 */
USword::USword()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Sword");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::SWORD;
	ItemMetaClass = USwordMeta::StaticClass();
	Socket = EEquipmentSocket::HAND;
	DescribeText = FText::FromString("A sword is an edged, bladed weapon intended for manual cutting or thrusting.");
	static ConstructorHelpers::FObjectFinder<UBlueprint> ActorBlueprint(TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Sword/Sword.Sword'"));
	if (ActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultItemEntityActorClass = ActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
}
