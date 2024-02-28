// Fill out your copyright notice in the Description page of Project Settings.


#include "../Object/Class/Item/Helmet.h"

#include "CharmingCraft/Interface/Meta/HelmetMeta.h"

UHelmet::UHelmet()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Helmet");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::HELMET;
	ItemMetaClass = UHelmetMeta::StaticClass();
	Socket = EEquipmentSocket::HEAD;
}

void UHelmet::OnEquipped()
{
	// 穿戴事件
}
