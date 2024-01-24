// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "UObject/Object.h"
#include "BaseBuffModel.generated.h"

class UBuffInfo;
class UDAttributeComponent;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBaseBuffModel : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UDAttributeComponent> AttributeComponent;

	UBaseBuffModel();

	/* */
	UPROPERTY(BlueprintReadWrite)
	int32 StackBounceModifer = 1;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Apply(UBuffInfo* BuffInfo, FHitData& HitData);
};
