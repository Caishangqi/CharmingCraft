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

	UFUNCTION(BlueprintCallable, Category = "Check")
	static FItemStackData GetItemStackDataInContainerByMaterial(EMaterial TargetMaterial, UInventoryComponent* TargetContainer)
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
};
