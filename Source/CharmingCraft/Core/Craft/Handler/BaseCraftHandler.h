// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharmingCraft/Core/Craft/RecipeRegistry.h"
#include "BaseCraftHandler.generated.h"

class UInventoryComponent;
class UBaseRecipeEntry;
/**
 * It is a prototyle class that is testing, it is design
 * for a recipe container to handle specific types of
 * recipe, for example the normal recipes contains array
 * of inputs and array of outputs
 *
 * however, user could extend the recipe class that specify
 * the ingridient be cost of mana, level or else, the specific
 * handler class is required to overriden ProcessRecipe()
 * function to handle different child recipe class
 */
UCLASS()
class CHARMINGCRAFT_API UBaseCraftHandler : public UObject
{
	GENERATED_BODY()

public:
	/*!
	 * Filter the collection of recipes by its classification, for example,
	 * group all "Material" recipe into a recipe pages
	 * 
	 * @param Classification Target Classification 
	 * @param RecipesContainerCollection 
	 * @return The Collection of recipes that have same classification
	 */
	TArray<UBaseRecipeEntry*> FilterRecipeByClassification(FName Classification,
	                                                       FRecipesContainerCollection& RecipesContainerCollection);

	/*!
	 * Process selected recipe from the speific recipe container, this function should
	 * only call from the recipe container
	 * 
	 * @param TargetRecipe The target recipe use want to process
	 * @param Amount The amount of process, for example, player craft 100 times recipes
	 * @param Container The Target container need to detect and handle deduct and output
	 * @param Instigator Who start the recipe process
	 * @return True if process succesful
	 */
	static bool ProcessRecipe(UBaseRecipeEntry* TargetRecipe, int32 Amount, UInventoryComponent* Container,
	                          UObject* Instigator);
};
