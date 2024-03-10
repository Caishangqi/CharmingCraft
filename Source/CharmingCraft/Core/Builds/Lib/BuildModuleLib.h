// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BuildModuleLib.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "Build Module Libarary"))
class CHARMINGCRAFT_API UBuildModuleLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FVector SnapToGrid(const FVector& OriginalPosition, float GridSize)
	{
		// 网格大小调整为网格的一半，用于对齐到XY平面的网格中心
		float HalfGridSize = GridSize * 0.5f;

		// 对X和Y轴进行偏移、四舍五入和回偏移以对齐到50x50的中心
		float X = FMath::RoundHalfToEven((OriginalPosition.X + HalfGridSize) / GridSize) * GridSize - HalfGridSize;
		float Y = FMath::RoundHalfToEven((OriginalPosition.Y + HalfGridSize) / GridSize) * GridSize - HalfGridSize;

		// Z轴保持原始的对齐逻辑，按照100单位网格对齐
		float Z = FMath::RoundHalfToEven(OriginalPosition.Z / GridSize) * GridSize;

		// 返回更新后的位置
		return FVector(X, Y, Z);
	}
};
