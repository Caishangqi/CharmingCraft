// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionCastLib.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "Action Cast Libarary"))
class CHARMINGCRAFT_API UActionCastLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Physics")
	static FRotator GetRotationBetweenTwoPoints(FVector StartPoint, FVector EndPoint)
	{
		FVector ToTarget = EndPoint - StartPoint;
		ToTarget.Normalize();

		const FRotator Rotation = ToTarget.Rotation();
		return Rotation;
	}
};
