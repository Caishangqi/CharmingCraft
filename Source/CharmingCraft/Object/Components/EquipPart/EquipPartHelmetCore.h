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

	UEquipPartHelmetCore();

	virtual void UpdateRenderMesh(EMaterial& NewComponentMaterialText) override;
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
};
