// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeOccludeStaicMeshComponent.h"
#include "CharmingCraft/Core/Log/Logging.h"

UNativeOccludeStaicMeshComponent::UNativeOccludeStaicMeshComponent()
{
}


void UNativeOccludeStaicMeshComponent::BeginPlay()
{
	// LogChamingCraftVisual
	Super::BeginPlay();
	GenerateOcclusionMaterialInstance();
	SetCollisionProfileName(TEXT("Occlusion"));
}

bool UNativeOccludeStaicMeshComponent::HideOccludedComponent_Implementation()
{
	if (!bIsAllowOcclude)
	{
		return false;
	}
	// Set Occlude Data
	bIsCurrentOcclude = true;

	UE_LOG(LogChamingCraftVisual, Warning, TEXT("Hide Occluded Component <%s>"), *this->GetName());
	for (UMaterialInterface* Material : GetMaterials())
	{
		Cast<UMaterialInstanceDynamic>(Material)->SetScalarParameterValue("Opacity", 0.16f);
	}

	OccludeMaterialInstance->SetScalarParameterValue("Opacity", 0.1f);

	return IOccludeObject::HideOccludedComponent_Implementation();
}

bool UNativeOccludeStaicMeshComponent::ShowOccludedComponent_Implementation()
{
	if (!bIsAllowOcclude)
	{
		return false;
	}

	UE_LOG(LogChamingCraftVisual, Display, TEXT("Show Occluded Component <%s>"), *this->GetName());
	// Set Occlude Data
	bIsCurrentOcclude = false;

	for (UMaterialInterface* Material : GetMaterials())
	{
		Cast<UMaterialInstanceDynamic>(Material)->SetScalarParameterValue("Opacity", 1.0f);
	}
	OccludeMaterialInstance->SetScalarParameterValue("Opacity", 0.0f);
	return IOccludeObject::ShowOccludedComponent_Implementation();
}

void UNativeOccludeStaicMeshComponent::GenerateOcclusionMaterialInstance()
{
	// Generate MID and set parameter for MID
	for (int i = 0; i < GetNumMaterials(); ++i)
	{
		CreateAndSetMaterialInstanceDynamic(i)->SetScalarParameterValue("Opacity", 1.0f);
	}


	// Generate and set parameter for Overlay Material
	OccludeMaterialInstance = UMaterialInstanceDynamic::Create(OccludeOverlayMaterial, this);
	OverlayMaterial = OccludeMaterialInstance;
	OccludeMaterialInstance->SetScalarParameterValue("Opacity", 0.0f);

	OccludeMaterials.Append(GetMaterials());
}
