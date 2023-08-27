// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/Meta/ArmorMeta.h"
#include "HelmetMeta.generated.h"

class UEquipPartArmorTrim;
class UEquipPartArmorPlates;
class UEquipPartHelmetCore;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UHelmetMeta : public UArmorMeta
{
	GENERATED_BODY()

public:

	UHelmetMeta();
	
	/* 属性 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Helmet Parts")
	UEquipPartHelmetCore* HelmetCore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Helmet Parts")
	UEquipPartArmorPlates* EquipPartArmorPlates;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Helmet Parts")
	UEquipPartArmorTrim* EquipPartArmorTrim;
};
