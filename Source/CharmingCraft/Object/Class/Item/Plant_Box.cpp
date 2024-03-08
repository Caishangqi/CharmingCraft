// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant_Box.h"

#include "CharmingCraft/Core/Item/Meta/BlockMeta.h"

UPlant_Box::UPlant_Box()
{
	DisplayName = FText::FromString("Plant Box");
	MaxStackSize = 64;
	ItemType = EItemType::BLOCK;
	Material = EMaterial::PLANT_BOX;
	ItemMetaClass = UBlockMeta::StaticClass();
	DescribeText = FText::FromString(
		"Planter boxes are great! They raise your garden up so that you don't have to bend over. They also look wonderful outdoors and come in all shapes and sizes.");

	static ConstructorHelpers::FObjectFinder<UBlueprint> BlockEntityActorBlueprint(
		TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Block/Farming/PlantBox.PlantBox'"));
	if (BlockEntityActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultBlockEntityActorClass = BlockEntityActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}

	// /Script/Engine.Blueprint'/Game/CharmingCraft/Resource/DropTable/DropTable_PlantBox.DropTable_PlantBox'
	static ConstructorHelpers::FObjectFinder<UBlueprint> DropTableDataFinder( // 只能寻找UE原生类型
		TEXT(
			"Blueprint'/Game/CharmingCraft/Resource/DropTable/DropTable_PlantBox.DropTable_PlantBox'"));
	// 检查是否成功找到了资源
	if (DropTableDataFinder.Succeeded())
	{
		// 找到类指针,在基于这个类指针进行默认对象建造
		DropTableData = DropTableDataFinder.Object->GeneratedClass->GetDefaultObject<UDropTableData>();
	}
}
