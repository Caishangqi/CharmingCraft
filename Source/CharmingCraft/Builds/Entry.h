// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Entry.generated.h"


UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEntry : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEntry();

	// The Entry Destination, assign in Editor
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UEntry> Destination;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString DestinationName;

	// Whether or not set visibility of origin level after entry sublevel
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bPostEntryOriginVisibility;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/*!
	 * Teleport Any Pawn to the specific DestinationName, you must load the stream
	 * level if you have then teleport or else the target point will be null
	 * @param TargetPawn The Pawn Actor you want to teleport to the destination
	 * @return whether or not find the target point
	 */
	UFUNCTION(BlueprintCallable)
	bool TeleportToDestination(APawn* TargetPawn);
};
