// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

UBlock::UBlock()
{
	// 位置 70, 85, 80
	FVector Position(100, 115, 115);
	// 旋转，这里使用欧拉角创建四元数旋转，假设只绕Z轴旋转90度
	//							green		blue		red
	FRotator3d Rotation(FRotator3d(325, 230, 0));
	//0, 325, 230
	// (Pitch=-35.000000,Yaw=-130.000000,Roll=-0.000000)
	FVector Scale(1, 1, 1);
	FTransform SceneCaptureRenderTransform(Rotation, Position, Scale);
	RenderSpecifyTransform = SceneCaptureRenderTransform;
	OrthoWidth = 192;
}
