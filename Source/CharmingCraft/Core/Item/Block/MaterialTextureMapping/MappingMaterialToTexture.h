// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "Engine/DataAsset.h"
#include "MappingMaterialToTexture.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UMappingMaterialToTexture : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MappingContext")
	TMap<EMaterial, TObjectPtr<UMaterialInstance>> MappingContext;
};
