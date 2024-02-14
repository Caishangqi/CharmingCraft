// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

bool UPlayerData::PerformSavePlayerDataToSlot(const UCharmingCraftInstance* GameInstance)
{
	URuntimeGameData * RuntimeGameData = GameInstance->GetRuntimeGameData();
	if (RuntimeGameData->PlayerCharacter && RuntimeGameData->PlayerCharacter
	                                                       ->
	                                                       GetLevel() && RuntimeGameData->PlayerCharacter->GetLevel()->
		GetWorld()
	)
	{
		PlayerLocation.PlayerLocation = RuntimeGameData->PlayerCharacter->GetActorLocation();
		PlayerLocation.LevelName = RuntimeGameData->PlayerCharacter->GetLevel()->GetName();
		UE_LOG(LogChamingCraftSave, Display, TEXT("[📥] Save PlayerDataPlayer Location: %s, WorldName: %s"),
		       *PlayerLocation.PlayerLocation.ToString(), *PlayerLocation.LevelName);
	}
	else
	{
		UE_LOG(LogChamingCraftSave, Warning, TEXT("PlayerCharacter, Level, or World is null."));
	}
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[📥] UPlayerDataSaveModel::Save()"))
	return true;
}
