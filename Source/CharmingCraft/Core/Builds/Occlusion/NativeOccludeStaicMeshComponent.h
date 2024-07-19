// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Interface/OccludeObject.h"
#include "Components/StaticMeshComponent.h"
#include "NativeOccludeStaicMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UNativeOccludeStaicMeshComponent : public UStaticMeshComponent, public IOccludeObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<UMaterialInterface*> OccludeMaterials;
	
	FTimerHandle NaturalPreOccludeTimer;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAllowOcclude = true;

	// Need refactory for better performance and can be replaced by Overlay material
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OccludeSettings")
	TObjectPtr<UMaterialInterface> OccludeMaterial;
	// Overlay material that apply when object occlude
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="OccludeSettings")
	TObjectPtr<UMaterialInterface> OccludeOverlayMaterial;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Occlude Data")
	bool bIsCurrentOcclude = false;

public:
	UNativeOccludeStaicMeshComponent();
	virtual bool GetIsOccluded_Implementation() const override { return bIsCurrentOcclude; }
	// 
	virtual void BeginPlay() override;

public:
	virtual bool HideOccludedComponent_Implementation() override;
	virtual bool ShowOccludedComponent_Implementation() override;
private:
	
	void GenerateOcclusionMaterialInstance();

	// Internal save of MID for Overlay Material
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> OccludeMaterialInstance;
};
