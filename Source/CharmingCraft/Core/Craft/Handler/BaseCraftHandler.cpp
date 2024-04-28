// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCraftHandler.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Container/Inventory/InventoryComponent.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

TArray<UBaseRecipeEntry*> UBaseCraftHandler::FilterRecipeByClassification(
	FName Classification, FRecipesContainerCollection& RecipesContainerCollection)
{
	TArray<UBaseRecipeEntry*> FilterOutPut;
	for (TObjectPtr<UBaseRecipeEntry> BaseRecipeEntry : RecipesContainerCollection.ContainerCollection)
	{
		if (BaseRecipeEntry->ContainerClassify.IsEqual(Classification))
		{
			FilterOutPut.Add(BaseRecipeEntry);
		}
	}
	return FilterOutPut;
}

bool UBaseCraftHandler::ProcessRecipe(UBaseRecipeEntry* TargetRecipe, int32 Amount, UInventoryComponent* Container,
                                      UObject* Instigator)
{
	TArray<FItemStackData> RecipeDeductOutput;
	// Generate Deduct output array
	for (FItemStackData Ingredient : TargetRecipe->Ingredients)
	{
		Ingredient.Amount = Ingredient.Amount * Amount;
		while (Container->FindSlotByMaterial(Ingredient.Material) != -1 && Ingredient.Amount > 0)
		{
			int32 TargetContainerIndex = Container->FindSlotByMaterial(Ingredient.Material);
			Container->Inventory[TargetContainerIndex]->Amount--;
			Ingredient.Amount--;
			if (Container->Inventory[TargetContainerIndex]->Amount == 0)
			{
				Container->Inventory[TargetContainerIndex] = nullptr;
			}
		}
		RecipeDeductOutput.Add(Ingredient);
		// At the end of process, the deduct array should have the same
		// number of FItemStackData campare with Ingredients and each
		// element should have amount of 0 (means all deduct success)
	}

	TArray<UItemStack*> RecipeOutPut;
	UGameEventHandler* EventHandler = Cast<UCharmingCraftInstance>(Container->GetOwner()->GetGameInstance())->
		GetGameEventHandler();
	// Secondary Check the deduct array
	for (FItemStackData& DeductOutput : RecipeDeductOutput)
	{
		// need to ensure deduct array's element Amount equal 0, or
		// it means it do not deduct container item success
		if (DeductOutput.Amount != 0)
		{
			EventHandler->OnCraftProcessFinishEnvent(TargetRecipe, Amount, false, Instigator, RecipeOutPut);
			Container->OnInventoryUpdate.Broadcast();
			return false;
		}
	}

	// Add output itemstacks into inventory
	for (FItemStackData& OutputItem : TargetRecipe->OutputItem)
	{
		RecipeOutPut.Add(
			UItemStack::CreateItemStackFromMaterial(Instigator, OutputItem.Material, OutputItem.Amount * Amount));
	}
	// Add the output product to container
	for (UItemStack* OutPut : RecipeOutPut)
	{
		Container->AddToInventory(OutPut);
	}

	EventHandler->OnCraftProcessFinishEnvent(TargetRecipe, Amount, true, Instigator, RecipeOutPut);
	// refresh the inventory and brodcast delegate to handle
	// UMG part of crafting system
	Container->OnInventoryUpdate.Broadcast();
	return true;
}
