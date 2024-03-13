// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Entity/Creature/Creature.h"
#include "CharmingCraft/Core/Resource/Data/FBiomeData.h"
#include "GameFramework/Volume.h"
#include "Biome.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ABiome : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName BiomeRegisterName;

	// Timer that check Internal Data in a biome
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CheckTickTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FBiomeData> RegisterBiomeData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBoxComponent> BiomeBound;

	// Record the ResourceEntityActor, can be watched by event system
	TArray<TObjectPtr<AResourceEntityActor>> ResourceEntityActorPool;
	TArray<TObjectPtr<ACreature>> CreaturesPool;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UGameEventHandler> GameEventHandler;

public:
	// Sets default values for this actor's properties
	ABiome();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool GetRandomPointInVolume(FVector& OutLocation);
	UFUNCTION()
	void OnResourceEntityBreakEvent(AActor* Breaker, AResourceEntityActor* TargetResourceEntity);
	
	float GetOnGenerateSuccessRate(FBiomeData BiomeData);
	bool StartBiomeDataTimer();
	void GenerateResource(FBiomeData BiomeData);

	void InitBiomeActor();
};
