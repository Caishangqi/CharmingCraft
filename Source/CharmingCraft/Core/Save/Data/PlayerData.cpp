// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"

#include "NativePlayerCharacter.h"
#include "RuntimeGameData.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

bool UPlayerData::PerformSavePlayerDataToSlot(const UCharmingCraftInstance* GameInstance)
{
	UE_LOG(LogChamingCraftSave, Display, TEXT("[📦] Saving INGAME Data to Slot: %s"),
	       *GameInstance->GetSaveManager()->CurrentSaveNode.SaveSlotName);
	// Save Location
	URuntimeGameData* RuntimeGameData = GameInstance->GetRuntimeGameData();
	if (RuntimeGameData->PlayerCharacter && RuntimeGameData->PlayerCharacter
	                                                       ->
	                                                       GetLevel() && RuntimeGameData->PlayerCharacter->GetLevel()->
		GetWorld()
	)
	{
		PlayerLocation.PlayerLocation = RuntimeGameData->PlayerCharacter->GetActorLocation();
		PlayerLocation.PlayerRotation = RuntimeGameData->PlayerCharacter->GetActorRotation();
		PlayerLocation.LevelName = RuntimeGameData->PlayerCharacter->GetLevel()->GetName();
		UE_LOG(LogChamingCraftSave, Display, TEXT("	[✅] Save PlayerDataPlayer Location: %s, WorldName: %s"),
		       *PlayerLocation.PlayerLocation.ToString(), *PlayerLocation.LevelName);
	}
	else
	{
		UE_LOG(LogChamingCraftSave, Warning, TEXT("PlayerCharacter, Level, or World is null."));
	}

	// Save Attribute Component
	TObjectPtr<ANativePlayerCharacter> PlayerCharacter = Cast<ANativePlayerCharacter>(RuntimeGameData->PlayerCharacter);
	if (PlayerCharacter)
	{
		AttributeComponentData = PlayerCharacter->AttributeComp->Serialize_Implementation();
		UE_LOG(LogChamingCraftSave, Display, TEXT("	[✅] Save AttributeComponentData to Player: %s, Health: %f"),
		       *PlayerCharacter.GetName(), PlayerCharacter->AttributeComp->Health)
	}

	UE_LOG(LogChamingCraftSave, Display, TEXT("	[✅] UPlayerDataSaveModel::Save()"))
	return true;
}
