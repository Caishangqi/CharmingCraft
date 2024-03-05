// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "UObject/Object.h"
#include "BuildModuleManager.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBuildModuleManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UItemStack> CachedBuildItemStack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Timer")
	FTimerHandle InternalTimer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="HitResult")
	FHitResult HitResult;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= "GridSize")
	float GridSize = 100.0f;

	UPROPERTY()
	TObjectPtr<ABlockEntityActor> BlockEntityActor;

	float UpdateTick = 0.1f;

public:
	UFUNCTION(BlueprintCallable)
	bool StartBuildPreviewTrace(UItemStack* PreviewItemStack, ACharacter* Instigator);
	UFUNCTION(BlueprintCallable)
	bool PlaceBuildPreview(ACharacter* Instigator);

private:
};
