// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "RegionChunkWidget.generated.h"


USTRUCT(BlueprintType)
struct FRegionChunkMetaData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString DisplayName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Discription;
};

UENUM(BlueprintType)
enum class ERegionState
{
	AVAILABLE,
	LOCKED,
	BLOCKED
};

/**
 * https://clockworkraven.itch.io/rpg-icon-pack-32-places-and-seasons
 */
UCLASS()
class CHARMINGCRAFT_API URegionChunkWidget : public UUserWidget, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ChunkNamespace;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> TargetWorld;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D ChunkCoordinate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> RegionBaseIcon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> RegionTopIcon;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRegionChunkMetaData RegionChunkMetaData;

public:
	UFUNCTION(BlueprintCallable)
	FLevelStreamingDynamicResult TravelToTargetWorld(APawn* Instigator);

	UFUNCTION(BlueprintCallable)
	bool CanPlayerTravelToRegion();

public:
	UFUNCTION(BlueprintCallable)
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	UFUNCTION(BlueprintCallable)
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
	UFUNCTION(BlueprintCallable)
	virtual UWorldManager* GetWorldManager_Implementation() override;
};
