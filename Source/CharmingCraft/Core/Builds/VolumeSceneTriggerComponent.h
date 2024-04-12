// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Camera/CameraManager.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "Components/BoxComponent.h"
#include "VolumeSceneTriggerComponent.generated.h"


UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UVolumeSceneTriggerComponent : public UBoxComponent, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UVolumeSceneTriggerComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool EnableChangeCameraView = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="EnableChangeCameraView"))
	bool EnableCustomCameraView = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool EnableCameraFade = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="EnableChangeCameraView"))
	ECameraPerspectiveEnum TargetCameraView;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="EnableCustomCameraView"))
	FCameraPerspective CustomCameraView;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DestinationName;

	// Whether or not set visibility of origin level after entry sublevel
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bPostEntryOriginVisibility;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> TargetLoadedLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> UnloadedLevel;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APawn> OverlappedActor;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnTargetLevelShown();

	void PostLevelCameraViewChange();
	// override
public:
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
	virtual UWorldManager* GetWorldManager_Implementation() override;
};
