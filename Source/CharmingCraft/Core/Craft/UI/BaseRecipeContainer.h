// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Craft/RecipeRegistry.h"
#include "CharmingCraft/Core/UI/Holder/WidgetHolder.h"
#include "BaseRecipeContainer.generated.h"

class UBaseCraftHandler;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBaseRecipeContainer : public UWidgetHolder
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ContainerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseCraftHandler> CraftHandlerClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBaseCraftHandler> CraftHandler;

	FRecipesContainerCollection* RecipesContainerCollection;

	virtual void NativeConstruct() override;
};
