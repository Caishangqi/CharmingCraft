// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Components/EquipPart/model/sword/EquipPartSwordPommel.h"
#include "EquipPartSwordPommelDecorative.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartSwordPommelDecorative : public UEquipPartSwordPommel
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipPartSwordPommelDecorative();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
