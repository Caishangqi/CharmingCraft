// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleItem.h"

UAppleItem::UAppleItem()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Apple");
	MaxStackSize = 64;

	
}

void UAppleItem::ConsumeForHealth()
{
}
