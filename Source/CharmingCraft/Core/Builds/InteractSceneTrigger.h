// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VolumeSceneTriggerComponent.h"
#include "../Core/Interact/NativeInteractActor.h"
#include "InteractSceneTrigger.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API AInteractSceneTrigger : public ANativeInteractActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractSceneTrigger();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool EnableCameraFade = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsASceneTravel = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="Craft World"))
	TSubclassOf<UNativeCraftWorld> TargetCraftWorld;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DestinationName;

	// Cached interact pawn used for callback
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APawn> InteractObject;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// override
public:
};
