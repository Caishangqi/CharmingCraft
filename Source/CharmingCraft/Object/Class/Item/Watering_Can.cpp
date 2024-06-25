// Fill out your copyright notice in the Description page of Project Settings.


#include "Watering_Can.h"
#include "CharmingCraft/Core/Builds/Module/BuildModuleManager.h"
#include "../Core/Item/Meta/Abstruct/IntegratedMeta.h"

UWatering_Can::UWatering_Can()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Watering Can");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::WATERING_CAN;
	ItemMetaClass = UIntegratedMeta::StaticClass();
	Socket = EEquipmentSocket::HAND;
	DescribeText = FText::FromString(
		"Watering Can can irrigate crops and increase growth rate. Different materials have different irrigation effects.");

	// (X=100.000000,Y=104.000000,Z=99.000000)
	// (Pitch=314.000000,Yaw=226.799342,Roll=0.000000)
	OrthoWidth = 128;
	RenderSpecifyTransform = FTransform(FRotator(314, 226, 0), FVector(100, 104, 100));

	// /Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Water_Can/watering_can.watering_can'

	static ConstructorHelpers::FObjectFinder<UBlueprint> ActorBlueprint(
		TEXT("Script/Engine.Blueprint'/Game/CharmingCraft/Item/ItemEntityActor/Water_Can/watering_can.watering_can'"));
	if (ActorBlueprint.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		DefaultItemEntityActorClass = ActorBlueprint.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
	
	// Default ItemDynamicSkill
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemActionComponentFinder(
		TEXT(
			"/Script/Engine.Blueprint'/Game/CharmingCraft/CraftComponents/Item/WaterCanDefaultActionComponent.WaterCanDefaultActionComponent'"));
	if (ItemActionComponentFinder.Succeeded())
	{
		UClass * Class = ItemActionComponentFinder.Object->GeneratedClass;
		ItemPredefineComponents.Add(Class);
	}
}

void UWatering_Can::OnEquip(UObject* Instigator, UItemStack* OnEquipItem)
{
	// Consider Combined BuildModel and Action Skills together.
	Super::OnEquip(Instigator, OnEquipItem);
}

void UWatering_Can::UnEquip(UObject* Instigator, UItemStack* UnEquipItem)
{
	Super::UnEquip(Instigator, UnEquipItem);

	// TODO: Add ItemSkill to Action Component and activate passive skills
}

void UWatering_Can::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator)
{
}
