// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Interface/UBreakable.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Core/Resource/Data/FResourceData.h"
#include "CharmingCraft/Core/Resource/Data/FResourceGeometryData.h"
#include "CharmingCraft/Core/Resource/Enum/EResourceType.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "ResourceEntityActor.generated.h"

class UGeometryCollectionComponent;
class UGameEventHandler;
class USceneComponent;
class UChildActorComponent;
class UBoxComponent;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API AResourceEntityActor : public AInteractObject, public IDamageable, public IBreakableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AResourceEntityActor();

	EResourceType ResourceType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Resource Register Name")
	FName ResourceName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Resource Current Stage")
	int32 CurrentStage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Resource Max Stage")
	int32 MaxStage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stage Entity Actor")
	TArray<TSubclassOf<AActor>> StageEntityActor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Resource Variation Entity Actor")
	TArray<TSubclassOf<AActor>> ResourceVariationEntityActor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Resource Geometry Data")
	FResourceGeometryData ResourceGeometryData;
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="默认")
	TObjectPtr<UBoxComponent> HitBox;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="默认")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Resource Data")
	FResourceData ResourceData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Timer")
	FTimerHandle ResourceInternalTimer;

	// Drop Table
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Drop Table")
	TSubclassOf<UDropTableData> DropTableData;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Drop Table")
	bool bDropSelf = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UGameEventHandler> GameEventHandler;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void ResetHealth();
	UFUNCTION(BlueprintCallable)
	int32 ReduceResourceHeath(int32 Delta);
	virtual bool OnBlockBreak_Implementation(AActor* Instigator, AActor* BlockBreak) override;
	virtual bool OnBlockDrop_Implementation(AActor* Block, UDropTableData* DropTableData) override;
	virtual void OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData) override;
};
