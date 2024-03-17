// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Module/BaseBuildModel.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "SeedsBuildModel.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API USeedsBuildModel : public UBaseBuildModel
{
	GENERATED_BODY()

public:
	USeedsBuildModel();

public:
	// Cached Item use for inventory item reduction
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItemStack> ModelCachedItemStack;
};
