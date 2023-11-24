// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/EquipPartSwordBlade.h"
#include "CharmingCraft/Object/Structs/model/sword/blade/FBladeBasicMaterial.h"
#include "EquipPartSwordBladeBasic.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartSwordBladeBasic : public UEquipPartSwordBlade
{
	GENERATED_BODY()

public:
	/* 属性 */
	FBladeBasicMaterial* MaterialProperties;
	
	// Sets default values for this component's properties
	UEquipPartSwordBladeBasic();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UpdateRenderMesh(EMaterial& NewComponentMaterialText) override;
};
