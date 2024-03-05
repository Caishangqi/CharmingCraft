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
		// 对每个坐标轴进行四舍五入到最近的网格点
		float X = FMath::RoundHalfToEven(OriginalPosition.X / GridSize) * GridSize;
		float Y = FMath::RoundHalfToEven(OriginalPosition.Y / GridSize) * GridSize;
		float Z = FMath::RoundHalfToEven(OriginalPosition.Z / GridSize) * GridSize;

		// 返回对齐后的位置
		return FVector(X, Y, Z);
	}
};
