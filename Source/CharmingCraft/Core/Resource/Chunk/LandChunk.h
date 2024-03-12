// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharmingCraft/Core/Resource/Data/FBiomeData.h"
#include "LandChunk.generated.h"

UCLASS()
class CHARMINGCRAFT_API ALandChunk : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALandChunk();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> BottomLayer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MiddleLayer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> TopLayer;
	/*!
	 * See https://forums.unrealengine.com/t/onconstruction-vs-blueprint-construction-script/362650
	 * @param bFinished 
	 */
	virtual void PostEditMove(bool bFinished) override;

	// Chunk information
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NumberCell_X = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NumberCell_Y = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 GridSize = 100;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> ChunkPoints;

	
	// Biome Information
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBiomeData> BiomeData;

	// Record the ResourceEntityActor, can be watched by event system
	TArray<TObjectPtr<AResourceEntityActor>> ResourceEntityActorPool;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UGameEventHandler> GameEventHandler;

	UFUNCTION()
	void OnResourceEntityBreakEvent(APawn* Breaker, AResourceEntityActor* TargetResourceEntity);
	float GetOnGenerateSuccessRate(FBiomeData BiomeData);
	bool StartBiomeDataTimer();
	/*!
	 * Generate Resource, first check box collision conner line trace, if
	 * 4 corner in the same plane, then trace the point generate the resource
	 * @param BiomeData The resource in Data you wan to generate
	 */
	void GenerateResource(FBiomeData BiomeData);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 GridCell_X;
	int32 GridCell_Y;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
};
