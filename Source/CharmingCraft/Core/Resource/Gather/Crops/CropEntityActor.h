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
	virtual bool OnBlockDrop_Implementation(AActor* Block, UDropTableData* DropTableData) override;
	virtual bool OnBlockBreak_Implementation(AActor* Instigator, AActor* BlockBreak) override;
	/*!
	 * Tick the growth at particular timer rate
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnGrowthTick();

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
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UDropTableData * GetDropTableFromGrowthStage();
	
	UFUNCTION(BlueprintCallable)
	int32 SetGrowthStage(int32 TargetStage);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CropData")
	FCropData CropData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="CropMesh")
	TObjectPtr<UStaticMeshComponent> CropMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Crop Medium")
	TObjectPtr<ABlockEntityActor> Medium;

	UPROPERTY(BlueprintReadWrite, Category="Crop Growth Timer")
	FTimerHandle CropGrowthTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Crop Stage")
	int32 CurrentStageCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnGrowthStageIncrease(int32 StageBefore);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
