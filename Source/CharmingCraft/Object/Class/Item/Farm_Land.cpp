// Fill out your copyright notice in the Description page of Project Settings.


#include "Farm_Land.h"

#include "CharmingCraft/Core/Item/Meta/BlockMeta.h"

UFarm_Land::UFarm_Land()
{
	DisplayName = FText::FromString("Farm Land");
	MaxStackSize = 64;
	ItemType = EItemType::BLOCK;
	Material = EMaterial::FARM_LAND;
	ItemMetaClass = UBlockMeta::StaticClass();
	DescribeText = FText::FromString("Agricultural land is typically land devoted to agriculture, the systematic and controlled use of other forms of life.");

	// /Script/Engine.Blueprint'/Game/CharmingCraft/Block/Farming/Farm_Land.Farm_Land'
	static ConstructorHelpers::FObjectFinder<UBlueprint> BlockEntityActorBlueprint(
	TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Block/Farming/Farm_Land.Farm_Land'"));
	if (BlockEntityActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultBlockEntityActorClass = BlockEntityActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
	
}
