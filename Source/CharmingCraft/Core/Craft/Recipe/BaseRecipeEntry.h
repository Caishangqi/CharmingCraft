// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/Data/FItemStack.h"
#include "Engine/DataAsset.h"
#include "BaseRecipeEntry.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UBaseRecipeEntry : public UDataAsset
{
	GENERATED_BODY()

public:
	// 配方名称
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString RecipeName;
	// 唯一标识
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName NameSpace;
	// 该配方展示到哪些容器中,这里的容器指的是UI或者机器
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName OwnerContainer;
	// 在当前容器中,该配方的更详细分类,比如说武器,药水,等等
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ContainerClassify;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recipe")
	TArray<FItemStackData> Ingredients;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recipe")
	TArray<FItemStackData> OutputItem;
};
