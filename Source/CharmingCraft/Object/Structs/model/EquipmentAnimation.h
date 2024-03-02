// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipmentAnimation.generated.h"

USTRUCT(Blueprintable)
struct FAttackStageAnimation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UAnimMontage> LeftAnimation;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UAnimMontage> RightAnimation;
};

class UEquipPartComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UEquipmentAnimation : public UPrimaryDataAsset
{
	GENERATED_BODY()
	/* 这是映射表,映射Material和ItemMeta之间的关系 */


public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="默认")
	TSubclassOf<UEquipPartComponent> EquipPartComponentClass;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FAttackStageAnimation> AttackStageAnimations;
};
