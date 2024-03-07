// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Data/FPlaceValidation.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "UObject/Object.h"
#include "BuildModuleManager.generated.h"

UENUM(BlueprintType)
enum class EBuildMode: uint8
{
	PLACE UMETA(DisplayName = "Place"),
	BREAK UMETA(DisplayName = "Break"),
};


/**
 * 
 */
class AFrameActor;

UCLASS()
class CHARMINGCRAFT_API UBuildModuleManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UItemStack> CachedBuildItemStack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Timer")
	FTimerHandle InternalTimer; // Internal Timer for line trace

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="HitResult")
	FHitResult HitResult;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= "GridSize")
	float GridSize = 100.0f; // Do not change grid size
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category= "Build Mode")
	EBuildMode CurrentBuildMode = EBuildMode::PLACE;

	UPROPERTY()
	TObjectPtr<ABlockEntityActor> BlockEntityActor;
	UPROPERTY()
	TObjectPtr<AFrameActor> HighlightFrameActor;
	TSubclassOf<AFrameActor> FrameActorClass;

	float UpdateTick = 0.1f; // Internal Timer Update Tick

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FPlaceValidation PlaceValidation; // Data collection that storage Collision info, and block data

	UBuildModuleManager();

public:
	/*!
	 * Trace from the player camera to mouse world position, hit static object will
	 * snap to grid then create preview BlockEntityActor set snapped location to the Actor
	 * @param PreviewItemStack ItemStack Input for read meta and Actor Class
	 * @param Instigator Who build or Start the trace
	 * @return Whether call successful
	 */
	UFUNCTION(BlueprintCallable)
	bool StartBuildPreviewTrace(UItemStack* PreviewItemStack, ACharacter* Instigator);
	UFUNCTION(BlueprintCallable)
	bool StartBreakPreviewTrace(ACharacter* Instigator);
	/*!
	 * Handle the place logic for Build Module system, check collision, if no collision occured
	 * place the block to world and decrease item amount in player inventory.
	 *
	 * @Future decrease logic should move into ItemClass, if some equipment could generate block
	 * @param Instigator Who Place the block
	 * @return Whether place successful or not
	 */
	UFUNCTION(BlueprintCallable)
	bool PlaceBuildPreview(ACharacter* Instigator);
	UFUNCTION(BlueprintCallable)
	bool BreakBlockPreview(ACharacter* Instigator);
	/*!
	 * Stop the timer and freeze the trace function
	 * Destroy the BlockEntityActor cache if it exist
	 */
	UFUNCTION(BlueprintCallable)
	void StopBuildPreview();
	UFUNCTION(BlueprintCallable)
	void StopBreakPreview();
	UFUNCTION(BlueprintCallable)
	void OnPlaceModeChange(ACharacter* Instigator, EBuildMode ToMode);
	UFUNCTION(BlueprintCallable)
	void RotatePreviewBlockLeft();
	UFUNCTION(BlueprintCallable)
	void RotatePreviewBlockRight();

private:
	/*!
	 * Load the correspond validation material to BlockEntityActor, enhance
	 * visual experience
	 */
	void LoadMaterialToPlaceValidation();
	/*!
	 * Save the Interact Object data, avoid player mouse move block and interact
	 * at same time
	 */
	void SaveBlockInteractProperties();
	/*!
	 * After Place the block, Block Should get the original Interact Object Class data
	 * @param BlockActor The Block that place in the world
	 * @param Data The Data that previously saved
	 */
	auto LoadBlockInteractProperties(ABlockEntityActor* BlockActor, const FPlaceValidation& Data) -> void;
};
