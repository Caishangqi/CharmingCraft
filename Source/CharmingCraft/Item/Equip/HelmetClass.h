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
UCLASS()
class CHARMINGCRAFT_API AHelmetClass : public ABaseEquipmentClass
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
};
