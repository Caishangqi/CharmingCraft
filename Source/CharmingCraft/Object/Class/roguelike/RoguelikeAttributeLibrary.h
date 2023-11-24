// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RoguelikeAttributeLibrary.generated.h"

struct FHitData;
/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "RouglikeAttributeLibrary"))
class CHARMINGCRAFT_API URoguelikeAttributeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	static bool IsAttackCriticFloat(float CriticValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	static bool IsAttackCriticInt(int32 CriticValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute Calculation")
	static int GetCriticalDamage(int32 SourceCriticalDamageEnhance, int32 TargetCriticalDamageDefenseEnhance);

	UFUNCTION(BlueprintCallable, Category = "Attribute Calculation")
	static float GetDamageReduce(int32 TargetProtect);

	UFUNCTION(BlueprintCallable, Category = "Attribute Calculation")
	static int GetDamage(int32 SourceDamage, int32 TargetProtect, bool bIsCritic = false,
	                     int32 OnHitCriticalDamage = 100);
};
