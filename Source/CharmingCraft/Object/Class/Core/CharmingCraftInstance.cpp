// Fill out your copyright notice in the Description page of Project Settings.


#include "CharmingCraftInstance.h"

#include "CharmingCraft/Core/GameMode/PlayerMode/PlayerModeManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Engine/DataTable.h"

UCharmingCraftInstance::UCharmingCraftInstance()
{
	// Load the DataTable using its path
	static ConstructorHelpers::FObjectFinder<UDataTable> ArmorMaterialDataTableFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/Armor_Materials.Armor_Materials'"));
	if (ArmorMaterialDataTableFinder.Succeeded())
	{
		ArmorMaterialDataTable = ArmorMaterialDataTableFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MaterialMetaMapperFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'"));
	if (MaterialMetaMapperFinder.Succeeded())
	{
		MaterialMetaMapper = MaterialMetaMapperFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> BladeBasicMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/blade/BladeBasicMaterial.BladeBasicMaterial'"));
	if (BladeBasicMaterialFinder.Succeeded())
	{
		BladeBasicMaterial = BladeBasicMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> FullerReinforcedMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/fuller/FullerReinforcedMaterial.FullerReinforcedMaterial'"));
	if (FullerReinforcedMaterialFinder.Succeeded())
	{
		FullerReinforcedMaterial = FullerReinforcedMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> GuardMakeShiftMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/guard/GuardMakeShiftMaterial.GuardMakeShiftMaterial'"));
	if (GuardMakeShiftMaterialFinder.Succeeded())
	{
		GuardMakeShiftMaterial = GuardMakeShiftMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> HiltBasicMaterialFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/hilt/HiltBasicMaterial.HiltBasicMaterial'"));
	if (HiltBasicMaterialFinder.Succeeded())
	{
		HiltBasicMaterial = HiltBasicMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> PommelDecorativeMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/pommel/PommelDecorativeMaterial.PommelDecorativeMaterial'"));
	if (PommelDecorativeMaterialFinder.Succeeded())
	{
		PommelDecorativeMaterial = PommelDecorativeMaterialFinder.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> RegisteredItemsFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'"));
	if (PommelDecorativeMaterialFinder.Succeeded())
	{
		RegisteredItems = RegisteredItemsFinder.Object;
	}
}

void UCharmingCraftInstance::Init()
{
	Super::Init();
	SaveManager = NewObject<UGameSaveManager>(this, UGameSaveManager::StaticClass());
	WorldManager = NewObject<UWorldManager>(this, UWorldManager::StaticClass());
	RuntimeGameData = NewObject<URuntimeGameData>(this, URuntimeGameData::StaticClass());

	GamePlayLogicManager = NewObject<UGameEventHandler>(this, UGameEventHandler::StaticClass());
	PlayerModeManager = NewObject<UPlayerModeManager>(this, UPlayerModeManager::StaticClass());

	UE_LOG(LogChamingCraftSave, Display, TEXT("[!] UCharmingCraftInstance::Init()"));
}

void UCharmingCraftInstance::OnStart()
{
	Super::OnStart();
	WorldManager->OnLevelLoaded.AddDynamic(GamePlayLogicManager, &UGameEventHandler::OnPlayerJoinEvent);
}
