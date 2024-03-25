// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeItemAction.h"
#include "NativeStandardMeleeAction.generated.h"
class ADCharacter;
class UCharmingCraftInstance;
/**
 * Handle Melee Action for an Item, especially the melee weapon
 * such as sword, pickaxe, hoe, etc
 *
 * The Class is an template, you should not create the instance
 * from this class
 */
struct FHitResult;
class AEquipmentEntityActor;

UCLASS()
class CHARMINGCRAFT_API UNativeStandardMeleeAction : public UNativeItemAction
{
	GENERATED_BODY()

public:
	// 
	UPROPERTY(BlueprintReadWrite)
	TArray<FHitResult> HitResults;

protected:
	FTimerHandle TraceTimer;
	// The Item "Model" that handle trace logic and collision
	// The Item Animation temporary store in 
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AEquipmentEntityActor> ItemEntityActor;
	// The List of Hit Actor when Item start their trace or collision
	UPROPERTY(BlueprintReadWrite)
	TSet<TObjectPtr<AActor>> HitActors;

public:
	UNativeStandardMeleeAction();

	// TODO: Consider new life cycle function such as OnInit() PostLoad()

	/*!
	 * Start trace , usually there are 2 points, bottom and top, do
	 * line trace through these 2 points
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action")
	void StartMeleeActionTrace();

	/*!
	 * Actual tick function handle the trace and fill hitActors
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action")
	void MeleeActionTick();

	/*!
	 * Apply function to hit actors, in weapon, it usually pass some damage
	 * see HitData
	 * @param HitEntity The Entity that been hit by line trace or collision
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action")
	void OnActionHit(AActor* HitEntity);

	/*!
	 * Stop the trace timer and apply function
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action")
	void EndMeleeActionTrace();

	virtual void StartAction_Implementation(APawn* Instigator) override;
};
