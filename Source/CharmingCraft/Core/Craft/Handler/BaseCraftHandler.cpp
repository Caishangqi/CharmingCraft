// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCraftHandler.h"
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
