// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FCropData.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "CharmingCraft/Core/Resource/Gather/ResourceEntityActor.h"
#include "CropEntityActor.generated.h"

UCLASS()
class CHARMINGCRAFT_API ACropEntityActor : public AResourceEntityActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACropEntityActor();

	virtual bool OnBlockPlace_Implementation(AActor* Instigator, AActor* BlockPlaced) override;
	/*!
	 * Tick the growth at particular timer rate
	 * @return CurrentStageCount 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 OnGrowthTick();

	/*!
	 * Start the Tick timer of crops
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartGrowthTick();

	/*!
	 * Stop the Tick timer of crops
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopGrowthTick();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CropData")
	FCropData CropData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CropMesh")
	TObjectPtr<UStaticMeshComponent> CropMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Crop Medium")
	TObjectPtr<ABlockEntityActor> Medium;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Crop Stage")
	int32 CurrentStage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Crop Stage")
	int32 CurrentStageCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
