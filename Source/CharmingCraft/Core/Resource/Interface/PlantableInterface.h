// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Resource/Gather/Crops/CropEntityActor.h"
#include "UObject/Interface.h"
#include "PlantableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPlantableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IPlantableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetGrowthMultiplier();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsOccupied();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ACropEntityActor* GetContainedCrop();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float UpdateGrowthMultiplier(float NewGrowthMultiplier);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetContainedCrop(ABlockEntityActor* Medium, ACropEntityActor* ContainedCrop);
};
