// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayLogicManager.h"

#include "EngineUtils.h"
#include "GameSaveManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "GameFramework/PlayerStart.h"
#include "Lib/CharacterSaveLib.h"

UGamePlayLogicManager::UGamePlayLogicManager()
{
	///Script/Engine.Blueprint'/Game/CharmingCraft/PlayerCharacter.PlayerCharacter'
	static ConstructorHelpers::FClassFinder<ADCharacter> BlueprintClass(
		TEXT("/Game/CharmingCraft/PlayerCharacter.PlayerCharacter"));

	if (BlueprintClass.Class != NULL)
	{
		BlueprintCharacterClassReference = BlueprintClass.Class;
	}
}

void UGamePlayLogicManager::OnPlayerJoinCallback()
{
}

void UGamePlayLogicManager::OnPlayerJoinBegin()
{
	//GetWorld()->SpawnActor<AActor>(BlueprintCharacterClassReference, Location, Rotation);


	APlayerStart* DesiredPlayerStart = nullptr;

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if (PlayerStart && PlayerStart->IsA(APlayerStart::StaticClass()))
		{
			// 可以添加更多的条件判断，来选择特定的PlayerStart
			DesiredPlayerStart = PlayerStart;
			break; // 如果您只有一个PlayerStart或者不需要特定的条件，找到一个后即可停止循环
		}
	}

	TObjectPtr<UCharmingCraftInstance> CharmingCraftInstance = Cast<UCharmingCraftInstance>(GetOuter());
	UPlayerData* PlayerData = CharmingCraftInstance->GetSaveManager()->GetCurrentSaveSlot().PlayerData;
	TObjectPtr<ACharacter> InGamePlayerCharacter = CharmingCraftInstance->GetRuntimeGameData()->PlayerCharacter;
	// Set Player Hidden First
	CharmingCraftInstance->GetRuntimeGameData()->PlayerCharacter->SetActorHiddenInGame(true);

	UE_LOG(LogChamingCraftGameLogic, Display, TEXT("[📨] UGamePlayLogicManager::OnPlayerJoinBegin()"));
	TObjectPtr<UMaterial> PlayerSkin = UCharacterSaveLib::FindPreviewMaterialFromCostumeId(
		CharmingCraftInstance->GetSaveManager()->InternalCostume,
		PlayerData->PlayerInfo.CostumeId);

	UCharacterSaveLib::ApplyCostumeToPlayer(
		InGamePlayerCharacter, PlayerSkin);

	// Handle Player Location
	if (!PlayerData->PlayerLocation.bIsSpawnPoint)
	{
		InGamePlayerCharacter->TeleportTo(
			PlayerData->PlayerLocation.PlayerLocation,
			PlayerData->PlayerLocation.PlayerRotation);
		PlayerData->PlayerLocation.bIsSpawnPoint = false;
	}
	else
	{
		PlayerData->PlayerLocation.bIsSpawnPoint = false;
	}


	// Set Player Visible After Load Location
	CharmingCraftInstance->GetRuntimeGameData()->PlayerCharacter->SetActorHiddenInGame(false);
}
