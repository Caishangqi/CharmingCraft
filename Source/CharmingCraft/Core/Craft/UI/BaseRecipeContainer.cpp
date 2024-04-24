// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRecipeContainer.h"

#include "CharmingCraft/Core/Craft/Handler/BaseCraftHandler.h"

void UBaseRecipeContainer::NativeConstruct()
{
	Super::NativeConstruct();

	CraftHandler = NewObject<UBaseCraftHandler>(this, CraftHandlerClass);

	// Fetch Data from Recipe Registry
	if (GetGameInstance_Implementation()->GetRecipeRegistry()->RegistedRecipe.Contains(ContainerName))
	{
		RecipesContainerCollection = GetGameInstance_Implementation()->GetRecipeRegistry()->RegistedRecipe.Find(ContainerName);
	}
}
