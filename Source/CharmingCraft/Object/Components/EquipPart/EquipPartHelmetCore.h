// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/EquipPartComponent.h"
#include "EquipPartHelmetCore.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UEquipPartHelmetCore : public UEquipPartComponent
{
	GENERATED_BODY()

public:
	/* 属性 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Component Properties")
	int32 PartProvidedResistance; //部件提供的抗性

	UEquipPartHelmetCore();
};
