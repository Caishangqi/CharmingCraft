// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenerateTraceLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "Generate Trace Library"))
class CHARMINGCRAFT_API UGenerateTraceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/*!
	 * Get the box low 4 conner
	 * @param Box The Box you wan to get its 4 conner
	 * @return The vector contain 4 conner location
	 */
	UFUNCTION(BlueprintCallable, Category = "Vector")
	static TArray<FVector> GetBoxCornerVector(UBoxComponent* Box)
	{
		FVector BoxOrigin = Box->GetComponentLocation();
		FVector BoxExtent = Box->GetScaledBoxExtent();
		FRotator BoxRotation = Box->GetRelativeRotation();

		TArray<FVector> Corners;
		Corners.SetNum(4);
		

		// Transform BoxExtent to local space rotation
		FQuat QuatRotation = FQuat(BoxRotation);

		// Bottom front right corner
		Corners[0] = BoxOrigin + QuatRotation.RotateVector(FVector(BoxExtent.X, BoxExtent.Y, -BoxExtent.Z));
		// Bottom front left corner
		Corners[1] = BoxOrigin + QuatRotation.RotateVector(FVector(-BoxExtent.X, BoxExtent.Y, -BoxExtent.Z));
		// Bottom back left corner
		Corners[2] = BoxOrigin + QuatRotation.RotateVector(FVector(-BoxExtent.X, -BoxExtent.Y, -BoxExtent.Z));
		// Bottom back right corner
		Corners[3] = BoxOrigin + QuatRotation.RotateVector(FVector(BoxExtent.X, -BoxExtent.Y, -BoxExtent.Z));

		return Corners;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Array")
	static bool AreAllElementsTheSame(const TArray<float>& Array)
	{
		if (Array.Num() <= 1)
		{
			// 如果数组为空或只有一个元素，则认为所有元素都是“相同的”
			return true;
		}

		// 获取数组的第一个元素作为比较基准
		const float& FirstElement = Array[0];

		// 从第二个元素开始遍历数组
		for (int32 Index = 1; Index < Array.Num(); ++Index)
		{
			if (!(Array[Index] == FirstElement))
			{
				// 如果发现有不同的元素，则立即返回false
				return false;
			}
		}

		// 如果所有元素都与第一个元素相同，则返回true
		return true;
	}
	
};
