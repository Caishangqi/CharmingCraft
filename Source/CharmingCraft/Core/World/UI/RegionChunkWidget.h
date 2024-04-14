// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "RegionChunkWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API URegionChunkWidget : public UUserWidget, public ICoreManagerInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> TargetWorld;
public:
	UFUNCTION(BlueprintCallable)
	FLevelStreamingDynamicResult TravelToTargetWorld(APawn * Instigator);
public:
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
	virtual UWorldManager* GetWorldManager_Implementation() override;
};
