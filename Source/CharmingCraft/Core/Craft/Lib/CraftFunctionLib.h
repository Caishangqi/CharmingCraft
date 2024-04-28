// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Container/Inventory/InventoryComponent.h"
#include "CharmingCraft/Core/Craft/Recipe/BaseRecipeEntry.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/Data/FItemStack.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CraftFunctionLib.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "CraftFunctionLibarary"))
class CHARMINGCRAFT_API UCraftFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*!
	 * Check a Container is matach with the recipes by Material
	 * @param TargetRecipe 
	 * @param TargetContainer 
	 * @return whether this recipe is craftable in the perspective of Material
	 */
	UFUNCTION(BlueprintCallable, Category = "Check")
	static bool GetCraftValidationMaterial(UBaseRecipeEntry* TargetRecipe, UInventoryComponent* TargetContainer)
	{
		for (FItemStackData& Ingredient : TargetRecipe->Ingredients)
		{
			FItemStackData SearchedResult = GetItemStackDataInContainerByMaterial(Ingredient.Material, TargetContainer);
			if (Ingredient.Material == SearchedResult.Material && Ingredient.Amount <= SearchedResult.Amount)
			{
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	/*!
	 * Get the ItemStack data from the specific container, inlcude Material and total amount,
	 * max stack size ignored
	 * @param TargetMaterial 
	 * @param TargetContainer 
	 * @return ItemStack data
	 */
	UFUNCTION(BlueprintCallable, Category = "Check")
	static FItemStackData GetItemStackDataInContainerByMaterial(EMaterial TargetMaterial,
	                                                            UInventoryComponent* TargetContainer)
	{
		FItemStackData ItemStackData;
		ItemStackData.Material = TargetMaterial;
		for (auto Element : TargetContainer->Inventory)
		{
			if (Element != nullptr && Element->Material == TargetMaterial)
			{
				ItemStackData.Amount += Element->Amount;
			}
		}
		return ItemStackData;
	}

	/*!
	 * Get the max recipes a container could affort
	 * @param TargetRecipe 
	 * @param TargetContainer 
	 * @return the max recipes number
	 */
	UFUNCTION(BlueprintCallable, Category = "Check")
	static int32 GetMaxAmountRecipeProcess(UBaseRecipeEntry* TargetRecipe, UInventoryComponent* TargetContainer)
	{
		TArray<int32> PerIngredientMaxAmount;
		for (FItemStackData& Ingredient : TargetRecipe->Ingredients)
		{
			FItemStackData SearchedResult = GetItemStackDataInContainerByMaterial(Ingredient.Material, TargetContainer);
			if (Ingredient.Material == SearchedResult.Material && Ingredient.Amount <= SearchedResult.Amount)
			{
				PerIngredientMaxAmount.Add((int)(SearchedResult.Amount / Ingredient.Amount));
			}
			else
			{
				return -1; // Invalid
			}
		}
		int32 Min = PerIngredientMaxAmount[0];
		for (int32 IngredientMaxAmount : PerIngredientMaxAmount)
		{
			if (IngredientMaxAmount < Min)
			Min = IngredientMaxAmount;
		}
		return Min;
	}
};
