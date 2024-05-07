// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DInteractionComponent.generated.h"


class ANativePlayerCharacter;
class ADPlayerAIController;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API UDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDInteractionComponent();
	/*!
	 * After line trace projection, the player would move to the actor they interact
	 * if the distance is not in the minimum range, then the player should move to
	 * the minimum range and execute interact methods
	 * 
	 * @param HitActor The actor that player interact
	 * @param HitLocation The location that player interact
	 * @return true if player interact within minimum range
	 * @return false if player need extra move to actor
	 */
	UFUNCTION(BlueprintCallable)
	bool PrimaryInteract(AActor* HitActor, FVector HitLocation);

	// TODO: This part could implement in a better way
	
	// The Callback function from Controller when execute OnMoveCompleted
	bool ExecuteInteractAction();
	void LineTracingInteract() const;
	void OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator);
	// Handle Callback function from Controller and handle creature damage
	bool ExecuteInteractWithCreature(AActor* TargetActor);

	/* Update Player Rotation */
	
	FGameplayTag InteractTag;

	// Event Related Logic
	/*!
	 * Player move to location while have a previous unfinished interact event,
	 * cancel the interact event by receiving OnPlayerMovementBroadcast from controller
	 * (especially the click move Input action)
	 * @param Instigator Who Cause move
	 * @param FromLocation From location
	 * @param TargetLocation To planned Target Location 
	 */
	UFUNCTION(BlueprintCallable)
	void OnPlayerMovementEvent(APawn* Instigator, FVector FromLocation, FVector TargetLocation);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ADPlayerAIController* AIController;

private:
	UPROPERTY()
	ANativePlayerCharacter* Player;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
