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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UBaseCraftHandler> CraftHandler;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRecipesContainerCollection RecipesContainerCollection;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	TArray<UBaseRecipeEntry*> FindRecipeByClassification(FName Classification); 
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	FRecipesContainerCollection GetRecipesContainerCollection();

};
