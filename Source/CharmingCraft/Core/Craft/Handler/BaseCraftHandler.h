// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharmingCraft/Core/Craft/RecipeRegistry.h"
#include "BaseCraftHandler.generated.h"

class UBaseRecipeEntry;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBaseCraftHandler : public UObject
{
	GENERATED_BODY()

public:
	TArray<UBaseRecipeEntry*> FilterRecipeByClassification(FName Classification, FRecipesContainerCollection & RecipesContainerCollection);
};
