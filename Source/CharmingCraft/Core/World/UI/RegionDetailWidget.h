// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RegionChunkWidget.h"
#include "CharmingCraft/Core/UI/Holder/WidgetHolder.h"
#include "RegionDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API URegionDetailWidget : public UWidgetHolder
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRegionChunkMetaData RegionChunkMetaData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> ChunkBaseImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> ChunkTopImage;
	
public:
	/*!
	 * Read the data from RegionChunkWidget and move RegionChunkWidget RegionChunkMetaData
	 * into URegionDetailWidget, usually call after constructor from RegionChunkWidget not
	 * in URegionDetailWidget
	 * @param RegionChunkWidget 
	 * @return true if set data correctly
	 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool ImportRegionData(URegionChunkWidget * RegionChunkWidget);
};
