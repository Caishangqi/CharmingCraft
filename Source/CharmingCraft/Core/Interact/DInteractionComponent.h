// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DInteractionComponent.generated.h"


class ADCharacter;
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
	//CancelInter

	bool ExecuteInteractAction();
	void LineTracingInteract() const;
	void OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator);

	/* Update Player Rotation */

	FGameplayTag InteractTag;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ADPlayerAIController* AIController;

private:
	UPROPERTY()
	ADCharacter* Player;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
