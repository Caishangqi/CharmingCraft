// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Resource/Enum/EResourceType.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "ResourceEntityActor.generated.h"

class USceneComponent;
class UChildActorComponent;
class UBoxComponent;

UCLASS()
class CHARMINGCRAFT_API AResourceEntityActor : public AInteractObject
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

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="默认")
	TObjectPtr<UBoxComponent> HitBox;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="默认")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
