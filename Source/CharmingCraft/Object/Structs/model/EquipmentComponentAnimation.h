// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipmentComponentAnimation.generated.h"

class UEquipPartComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UEquipmentComponentAnimation : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="默认")
	TSubclassOf<UEquipPartComponent> EquipPartComponentClass;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="默认")
	TArray<UAnimMontage*> AttackStageAnimation;
};
