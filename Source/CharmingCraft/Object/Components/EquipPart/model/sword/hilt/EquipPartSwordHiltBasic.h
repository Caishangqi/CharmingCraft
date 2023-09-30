// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/EquipPartSwordHilt.h"
#include "CharmingCraft/Object/Structs/model/sword/hilt/FHiltBasicMaterial.h"
#include "EquipPartSwordHiltBasic.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartSwordHiltBasic : public UEquipPartSwordHilt
{
	GENERATED_BODY()

public:

	/* 属性 */
	FHiltBasicMaterial * MaterialProperties;
	
	// Sets default values for this component's properties
	UEquipPartSwordHiltBasic();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UpdateRenderMesh(EMaterial& NewComponentMaterialText) override;
};
