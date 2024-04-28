// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRecipeContainer.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Craft/Handler/BaseCraftHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"

TArray<UBaseRecipeEntry*> UBaseRecipeContainer::FindRecipeByClassification_Implementation(FName Classification)
{
	FRecipesContainerCollection Collection = GetRecipesContainerCollection();
	return CraftHandler->FilterRecipeByClassification(Classification, Collection);
}


void UBaseRecipeContainer::NativeConstruct()
{
	Super::NativeConstruct();


	CraftHandler = NewObject<UBaseCraftHandler>(this, CraftHandlerClass);
	RecipesContainerCollection = GetGameInstance_Implementation()->RecipeRegistry->RegistedRecipe.
	                                                               FindRef(ContainerName);
	// TODO: need investigate why RecipesContainerCollection is nullptr after the function stack
	
}

FRecipesContainerCollection UBaseRecipeContainer::GetRecipesContainerCollection()
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

bool UBaseRecipeContainer::StartProcessRecipe(UBaseRecipeEntry* TargetRecipe, int32 Amount,
                                              UInventoryComponent* Container,
                                              UObject* Instigator)
{
	GetGameEventHandler_Implementation()->OnCraftProcessStartEvent(TargetRecipe, Amount, Container, Instigator);
	return CraftHandler->ProcessRecipe(TargetRecipe, Amount, Container, Instigator);
}
