// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/EquipPartSwordGuard.h"
#include "CharmingCraft/Object/Structs/model/sword/guard/FGuardMakeShiftMaterial.h"
#include "EquipPartSwordGuardMakeShift.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartSwordGuardMakeShift : public UEquipPartSwordGuard
{
	GENERATED_BODY()

public:

	/* 属性 */
	FGuardMakeShiftMaterial * MaterialProperties;
	
	// Sets default values for this component's properties
	UEquipPartSwordGuardMakeShift();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UpdateRenderMesh(EMaterial& NewComponentMaterialText) override;
};
