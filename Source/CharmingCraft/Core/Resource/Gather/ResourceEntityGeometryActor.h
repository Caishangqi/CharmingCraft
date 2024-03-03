// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "ResourceEntityGeometryActor.generated.h"

UCLASS()
class CHARMINGCRAFT_API AResourceEntityGeometryActor : public AGeometryCollectionActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AResourceEntityGeometryActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Timer")
	int32 LifeTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Timer")
	FTimerHandle InternalDestroyTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Timer")
	FTimerHandle InternalDecorationTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY() // Use for opacity change
	TObjectPtr<UMaterialInstanceDynamic> MaterialInstanceDynamic;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyResourceEntityGeometryActor();
	UFUNCTION(BlueprintCallable)
	void ApplyResourceEntityDecoration();
};
