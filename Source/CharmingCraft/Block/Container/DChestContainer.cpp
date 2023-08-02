// Fill out your copyright notice in the Description page of Project Settings.


#include "DChestContainer.h"

void ADChestContainer::Interact_Implementation(APawn* InstigatorPawn)
{
	/*
	 *	箱子被玩家互动后执行的开箱操作
	 *	SetRelativeRotation 中的Relative是相对于LidMesh 连接的组件这里相对的应该是BaseMesh
	 *	FRotator(TargetPitch,0,0) 对应的是旋转向量旋转向量的仰角为Pitch也就是Y (绿色的)
	 */
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

ADChestContainer::ADChestContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110; //初始化,默认变量
}
