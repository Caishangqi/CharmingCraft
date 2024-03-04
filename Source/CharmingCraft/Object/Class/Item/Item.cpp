// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
	MaxStackSize = 64;
	// 
	FVector Position(100.0, 85.0, 70.0);
	// 旋转，这里使用欧拉角创建四元数旋转，假设只绕Z轴旋转90度
	FQuat Rotation(FRotator(0, -120.0, 0));
	// 缩放
	FVector Scale(1, 1, 1);
	FTransform SceneCaptureRenderTransform(Rotation, Position, Scale);
	RenderSpecifyTransform = SceneCaptureRenderTransform;
	OrthoWidth = 164;
}

void UItem::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator)
{
}

void UItem::EndItemInteract()
{
}
