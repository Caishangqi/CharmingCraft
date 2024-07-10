// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Interface/OccludeObject.h"
#include "Components/StaticMeshComponent.h"
#include "OccludeStaicMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UOccludeStaicMeshComponent : public UStaticMeshComponent, public IOccludeObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<UMaterialInterface*> OccludeMaterials;

	FTimerHandle NaturalPreOccludeTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAllowOcclude = true;

public:

	UOccludeStaicMeshComponent();
	// 
	virtual void BeginPlay() override;

public:
	virtual bool HideOccludedComponent_Implementation() override;
	virtual bool ShowOccludedComponent_Implementation() override;
};
