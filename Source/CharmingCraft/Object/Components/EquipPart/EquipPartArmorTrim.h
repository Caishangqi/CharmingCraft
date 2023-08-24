// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/EquipPartComponent.h"
#include "EquipPartArmorTrim.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartArmorTrim : public UEquipPartComponent
{
	GENERATED_BODY()

public:
	/*属性*/


	/* 提供的耐久 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Component Properties")
	int32 PartProvidedDurability; //

	UEquipPartArmorTrim();
};
