// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeRegionChunkWidget.h"
#include "CharmingCraft/Core/UI/Holder/WidgetHolder.h"
#include "NativeRegionDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UNativeRegionDetailWidget : public UWidgetHolder
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
	 * into UNativeRegionDetailWidget, usually call after constructor from RegionChunkWidget not
	 * in UNativeRegionDetailWidget
	 * @param RegionChunkWidget 
	 * @return true if set data correctly
	 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool ImportRegionData(UNativeRegionChunkWidget * RegionChunkWidget);
};
