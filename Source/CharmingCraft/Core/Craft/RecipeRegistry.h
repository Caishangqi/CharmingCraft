// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Recipe/BaseRecipeEntry.h"
#include "UObject/Object.h"
#include "RecipeRegistry.generated.h"

USTRUCT(BlueprintType)
struct FRecipesContainerCollection
{
	GENERATED_BODY()

public:
	FRecipesContainerCollection(): ContainerCollection()
	{
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TObjectPtr<UBaseRecipeEntry>> ContainerCollection;
};

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API URecipeRegistry : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, FRecipesContainerCollection> RegistedRecipe;

	UFUNCTION(BlueprintCallable)
	bool RegistRecipeFromClass();

private:
};
