// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharmingCraft/Core/Resource/Data/FBiomeData.h"
#include "LandChunk.generated.h"

UENUM(BlueprintType)
enum class EChunkState
{
	// The chunk is loaded and generate resource periodically
	LOADED,
	// the chunk is marked pending unloaded, disable resource periodically
	PENDING_UNLOADED,
	// the chunk is unloaded and can be serialize
	UNLOADED
};

UCLASS()
class CHARMINGCRAFT_API ALandChunk : public AActor, public ICoreManagerInterface
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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EChunkState ChunkState = EChunkState::LOADED;

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

	// Record the NativeCreatureActor, can be watched by event system
	TArray<TObjectPtr<ANativeCreature>> NativeCreaturePool;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UGameEventHandler> GameEventHandler;

	// Delegate based call event, faster but may cause concurrent issue
	UFUNCTION(BlueprintCallable)
	void OnUnloadWorldChunk(UObject* InstigatorObject, ALandChunk* TargetChunk);
	UFUNCTION(BlueprintCallable)
	void SpawnCreatureAtChunk();
	UFUNCTION(BlueprintCallable)
	void OnLoadWorldChunk(UObject* InstigatorObject, ALandChunk* TargetChunk);

	UFUNCTION()
	void OnResourceEntityBreakEvent(AActor* Breaker, AResourceEntityActor* TargetResourceEntity);
	float GetOnGenerateResourceSuccessRate(FBiomeData BiomeData, UClass* ResourceClass);
	bool StartBiomeDataTimer();
	/*!
	 * Generate Resource, first check box collision conner line trace, if
	 * 4 corner in the same plane, then trace the point generate the resource
	 * @param BiomeData The resource in Data you wan to generate
	 */
	void SpawnResourceEntity(FBiomeData BiomeData);
	void SpawnCreatureEntity(FBiomeData BiomeData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	int32 GridCell_X;
	int32 GridCell_Y;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
	virtual UWorldManager* GetWorldManager_Implementation() override;

private:
};
