// Fill out your copyright notice in the Description page of Project Settings.


#include "../Object/Class/Item/Helmet.h"

UHelmet::UHelmet()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Helmet");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
}

void UHelmet::OnEquipped()
{
	// 穿戴事件
}
