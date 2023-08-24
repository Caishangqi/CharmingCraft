// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/BaseEquipmentClass.h"
#include "HelmetClass.generated.h"

class UEquipPartArmorTrim;
class UEquipPartArmorPlates;
class UEquipPartHelmetCore;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UHelmetClass : public UBaseEquipmentClass
{
	GENERATED_BODY()

public:
	/* 属性 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Helmet Parts")
	UEquipPartHelmetCore* HelmetCore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Helmet Parts")
	UEquipPartArmorPlates* EquipPartArmorPlates;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Helmet Parts")
	UEquipPartArmorTrim* EquipPartArmorTrim;

	UHelmetClass();
};
