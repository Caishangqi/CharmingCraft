// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"

#include "CharmingCraft/Object/Components/ItemStack.h"

ADropItem::ADropItem()
{
	ItemStack = CreateDefaultSubobject<UItemStack>("Default ItemStack");


	// 创建一个USceneComponent并将其设置为根组件
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	DropIconMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropIconMesh"));
	DropIconMesh->SetupAttachment(RootComponent); // 附加到Root组件
	// 设置旋转
	FRotator DropIconRotation = FRotator(30.0f, 0.0f, -90.0f); // Pitch, Yaw, Roll
	FVector DropIconLocation = FVector(0.0f, 0.0f, 32.0f); // X, Y, Z
	DropIconMesh->SetRelativeLocation(DropIconLocation);
	DropIconMesh->SetRelativeRotation(DropIconRotation);

	DropModelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropModelMesh"));
	DropModelMesh->SetupAttachment(RootComponent); //
}
