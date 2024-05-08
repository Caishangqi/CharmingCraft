// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VolumeSceneTriggerComponent.h"
#include "CharmingCraft/Core/Camera/CameraManager.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "InteractSceneTrigger.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API AInteractSceneTrigger : public AInteractObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractSceneTrigger();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool EnableChangeCameraView = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="EnableChangeCameraView"))
	bool EnableCustomCameraView = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool EnableCameraFade = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsASceneTravel = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bIsASceneTravel"))
	bool bResetSceneData = false;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="EnableChangeCameraView"))
	ECameraPerspectiveEnum TargetCameraView;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="EnableCustomCameraView"))
	FCameraPerspective CustomCameraView;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DestinationName;
	// The Level need load when interact this trigger
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bIsASceneTravel"))
	TSoftObjectPtr<UWorld> TargetLoadedLevel;
	//  The Level need unload when interact this trigger
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bIsASceneTravel"))
	TSoftObjectPtr<UWorld> UnloadedLevel;
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

	UFUNCTION(BlueprintCallable)
	void OnTargetLevelShown();
	UFUNCTION(BlueprintCallable)
	void OnTargetLevelHidden();

	void PostLevelCameraViewChange();

	// override
public:
};
