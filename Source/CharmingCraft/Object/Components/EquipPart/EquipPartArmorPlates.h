// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/EquipPartComponent.h"
#include "EquipPartArmorPlates.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UEquipPartArmorPlates : public UEquipPartComponent
{
	GENERATED_BODY()

public:
	/* 属性 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Component Properties")
	int32 PartProvidedArmor; //部件提供的护甲

	UEquipPartArmorPlates();
};
