// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entry.h"
#include "LevelTargetPoint.h"
#include "GameFramework/Actor.h"
#include "Build.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ABuild : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuild();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building Information")
	FString BuildName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SceneComponent")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building Mesh")
	TObjectPtr<UStaticMeshComponent> BuildingMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="SubLevel")
	TSoftObjectPtr<UWorld> SubLevelEntry;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="BuildingEntry")
	TObjectPtr<UEntry> BuildingEntry;

	// Building Default Exit location, use for interior subspace teleport
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BuildingEntry")
	TObjectPtr<UChildActorComponent> BuildingExitPoint;
};
