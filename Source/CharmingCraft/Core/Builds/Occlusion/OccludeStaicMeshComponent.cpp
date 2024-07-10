// Fill out your copyright notice in the Description page of Project Settings.


#include "OccludeStaicMeshComponent.h"

#include "CharmingCraft/Core/Log/Logging.h"

UOccludeStaicMeshComponent::UOccludeStaicMeshComponent()
{
}

void UOccludeStaicMeshComponent::BeginPlay()
{
	// LogChamingCraftVisual
	Super::BeginPlay();
	OccludeMaterials.Append(GetMaterials());
	SetCollisionProfileName(TEXT("Occlusion"));
}

bool UOccludeStaicMeshComponent::HideOccludedComponent_Implementation()
{
	UE_LOG(LogChamingCraftVisual, Warning, TEXT("Hide Occluded Component <%s>"), *this->GetName());
	return IOccludeObject::HideOccludedComponent_Implementation();
}

bool UOccludeStaicMeshComponent::ShowOccludedComponent_Implementation()
{
	UE_LOG(LogChamingCraftVisual, Display, TEXT("Show Occluded Component <%s>"), *this->GetName());
	return IOccludeObject::ShowOccludedComponent_Implementation();
}
