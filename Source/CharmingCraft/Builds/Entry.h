// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
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
};
