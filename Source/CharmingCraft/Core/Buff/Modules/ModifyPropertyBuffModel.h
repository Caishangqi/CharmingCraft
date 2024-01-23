// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"
#include "CharmingCraft/Core/Buff/BaseBuffModel.h"
#include "ModifyPropertyBuffModel.generated.h"

/**
 * Modified Buff Model: Handle Buff modified Attributes, Add only
 */
UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API UModifyPropertyBuffModel : public UBaseBuffModel
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UDAttributeComponent> AttributeComponent;

	/* The Delta Value you want to apply to Target or Instigator Attribute */
	UPROPERTY(BlueprintReadWrite)
	FPlayerAttribute PlayerAttributeDelta; // Remember remove after buff is over

	virtual void Apply_Implementation(UBuffInfo* BuffInfo, FHitData& HitData) override;
};
