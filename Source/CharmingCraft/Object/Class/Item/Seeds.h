// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "CharmingCraft/Core/Resource/Gather/Crops/CropEntityActor.h"
#include "Seeds.generated.h"

/**
 * 
 */
class UBaseBuildModel;

UCLASS()
class CHARMINGCRAFT_API USeeds : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSubclassOf<UBaseBuildModel> BuildModel;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSubclassOf<ACropEntityActor> CropEntityClass;

	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator) override;
};
