// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Craft/RecipeRegistry.h"
#include "CharmingCraft/Core/UI/Holder/WidgetHolder.h"
#include "NativeBaseRecipeContainer.generated.h"

class UBaseCraftHandler;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UNativeBaseRecipeContainer : public UWidgetHolder
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ContainerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseCraftHandler> CraftHandlerClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UBaseCraftHandler> CraftHandler;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRecipesContainerCollection RecipesContainerCollection;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<UBaseRecipeEntry*> FindRecipeByClassification(FName Classification);

	virtual void NativeConstruct() override;

	/*!
	 * Returns The Recipe collection for this Recipe collection, for example,
	 * the "primary craft" container contain many recipes who's container is
	 * "primary craft", fetching those collection from recipe registy
	 * 
	 * @return FRecipesContainerCollection- The Recipe collection for this Recipe collection
	 */
	UFUNCTION(BlueprintCallable)
	FRecipesContainerCollection GetRecipesContainerCollection();

	UFUNCTION(BlueprintCallable)
	bool StartProcessRecipe(UBaseRecipeEntry* TargetRecipe, int32 Amount, UInventoryComponent* Container,
	                        UObject* Instigator);
};
