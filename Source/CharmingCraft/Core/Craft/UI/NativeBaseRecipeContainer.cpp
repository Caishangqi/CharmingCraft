// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeBaseRecipeContainer.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Craft/Handler/BaseCraftHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"

TArray<UBaseRecipeEntry*> UNativeBaseRecipeContainer::FindRecipeByClassification_Implementation(FName Classification)
{
	FRecipesContainerCollection Collection = GetRecipesContainerCollection();
	return CraftHandler->FilterRecipeByClassification(Classification, Collection);
}


void UNativeBaseRecipeContainer::NativeConstruct()
{
	Super::NativeConstruct();


	CraftHandler = NewObject<UBaseCraftHandler>(this, CraftHandlerClass);
	RecipesContainerCollection = GetGameInstance_Implementation()->RecipeRegistry->RegistedRecipe.
	                                                               FindRef(ContainerName);
	// TODO: need investigate why RecipesContainerCollection is nullptr after the function stack
	
}

FRecipesContainerCollection UNativeBaseRecipeContainer::GetRecipesContainerCollection()
{
	if (GetGameInstance_Implementation())
	{
		return *GetGameInstance_Implementation()->RecipeRegistry->RegistedRecipe.Find(ContainerName);
	}
	else
	{
		return FRecipesContainerCollection();
	}
}

bool UNativeBaseRecipeContainer::StartProcessRecipe(UBaseRecipeEntry* TargetRecipe, int32 Amount,
                                              UInventoryComponent* Container,
                                              UObject* Instigator)
{
	GetGameEventHandler_Implementation()->OnCraftProcessStartEvent(TargetRecipe, Amount, Container, Instigator);
	return CraftHandler->ProcessRecipe(TargetRecipe, Amount, Container, Instigator);
}
