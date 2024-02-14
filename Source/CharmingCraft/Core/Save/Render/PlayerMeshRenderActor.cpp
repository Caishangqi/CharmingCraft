// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMeshRenderActor.h"

#include "EPlayerPreviewLocation.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Core/Save/Lib/CharacterSaveLib.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"


// Sets default values
APlayerMeshRenderActor::APlayerMeshRenderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerMeshRenderActor::BeginPlay()
{
	Super::BeginPlay();
	GameSaveManager = Cast<UCharmingCraftInstance>(GetGameInstance())->GetSaveManager();
}

// Called every frame
void APlayerMeshRenderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerMeshRenderActor::HideActor()
{
	this->SetActorHiddenInGame(true);
}

void APlayerMeshRenderActor::ShowActor()
{
	this->SetActorHiddenInGame(false);
}

bool APlayerMeshRenderActor::UpdatePreviewBaseSaveManager()
{
	if (GameSaveManager->GetValidSaveSlotsRingNumber() <= 2)
	{
		switch (PreviewLocation)
		{
		case EPlayerPreviewLocation::Left:
			if (IsPreviewLocationValidSlot())
			{
				PreviewMaterial = UCharacterSaveLib::FindPreviewMaterialFromCostumeId(
					GameSaveManager->InternalCostume,
					GameSaveManager->GetPreviewSlot().PlayerData->PlayerInfo.CostumeId);
				UCharacterSaveLib::ApplyPreviewCostumeToPlayer(this, PreviewMaterial);
				ShowActor();
			}
			else
			{
				HideActor();
			}
			break;
		case EPlayerPreviewLocation::Middle:
			if (IsPreviewLocationValidSlot())
			{
				PreviewMaterial = UCharacterSaveLib::FindPreviewMaterialFromCostumeId(
					GameSaveManager->InternalCostume,
					GameSaveManager->GetCurrentSaveSlot().PlayerData->PlayerInfo.CostumeId);
				UCharacterSaveLib::ApplyPreviewCostumeToPlayer(this, PreviewMaterial);
				ShowActor();
			}
			else
			{
				HideActor();
			}
			break;
		case EPlayerPreviewLocation::Right:
			HideActor();
			break;
		}
	}
	else
	{
		switch (PreviewLocation)
		{
		case EPlayerPreviewLocation::Left:
			if (IsPreviewLocationValidSlot())
			{
				ShowActor();
				PreviewMaterial = UCharacterSaveLib::FindPreviewMaterialFromCostumeId(
					GameSaveManager->InternalCostume,
					GameSaveManager->GetPreviewSlot().PlayerData->PlayerInfo.CostumeId);
				UCharacterSaveLib::ApplyPreviewCostumeToPlayer(this, PreviewMaterial);
			}
			else
			{
				HideActor();
			}
			break;
		case EPlayerPreviewLocation::Middle:
			if (IsPreviewLocationValidSlot())
			{
				ShowActor();
				PreviewMaterial = UCharacterSaveLib::FindPreviewMaterialFromCostumeId(
					GameSaveManager->InternalCostume,
					GameSaveManager->GetCurrentSaveSlot().PlayerData->PlayerInfo.CostumeId);
				UCharacterSaveLib::ApplyPreviewCostumeToPlayer(this, PreviewMaterial);
			}
			else
			{
				HideActor();
			}
			break;
		case EPlayerPreviewLocation::Right:
			if (IsPreviewLocationValidSlot())
			{
				ShowActor();
				PreviewMaterial = UCharacterSaveLib::FindPreviewMaterialFromCostumeId(
					GameSaveManager->InternalCostume,
					GameSaveManager->GetNextSlot().PlayerData->PlayerInfo.CostumeId);
				UCharacterSaveLib::ApplyPreviewCostumeToPlayer(this, PreviewMaterial);
			}
			else
			{
				HideActor();
			}
			break;
		}
	}

	return false;
}

bool APlayerMeshRenderActor::IsPreviewLocationValidSlot()
{
	switch (PreviewLocation)
	{
	case EPlayerPreviewLocation::Left:
		return !GameSaveManager->GetPreviewSlot().IsIndicateBound;
	case EPlayerPreviewLocation::Middle:
		return !GameSaveManager->GetCurrentSaveSlot().IsIndicateBound;
	case EPlayerPreviewLocation::Right:
		return !GameSaveManager->GetNextSlot().IsIndicateBound;
	default:
		return false;
	}
}
