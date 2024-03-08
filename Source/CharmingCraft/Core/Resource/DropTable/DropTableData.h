// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "Engine/DataAsset.h"
#include "DropTableData.generated.h"


USTRUCT(BlueprintType)
struct FDropData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EMaterial Material;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxAmount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MinimumAmount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Chance;
};

USTRUCT(BlueprintType)
struct FDropList
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EMaterial, int32> DropContext;
};

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UDropTableData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DropTableName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FDropData> DropContext;

public:
};
