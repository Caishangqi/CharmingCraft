// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Interface/EquipPartComponent.h"
#include "EquipPartSwordBlade.generated.h"


class UEquipmentComponentAnimation;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartSwordBlade : public UEquipPartComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipPartSwordBlade();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
