// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Core/GameMode/PlayerMode/PlayerModeManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "CharmingCraft/Core/Builds/Module/BuildModuleManager.h"
#include "CharmingCraft/Core/Camera/CameraManager.h"
#include "CharmingCraft/Core/Craft/RecipeRegistry.h"
#include "CharmingCraft/Core/Save/Data/RuntimeGameData.h"
#include "Dungeon/NativeDungeonHandler.h"
#include "Engine/DataTable.h"
#include "World/TimeManager.h"

UCharmingCraftInstance::UCharmingCraftInstance(): SaveManager(nullptr), WorldManager(nullptr),
                                                  GamePlayLogicManager(nullptr),
                                                  RuntimeGameData(nullptr),
                                                  PlayerModeManager(nullptr),
                                                  BuildModuleManager(nullptr),
                                                  CameraManager(nullptr)
{
	// Load the DataTable using its path
	static ConstructorHelpers::FObjectFinder<UDataTable> ArmorMaterialDataTableFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/Armor_Materials.Armor_Materials'"));
	if (ArmorMaterialDataTableFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *ArmorMaterialDataTableFinder.Object.GetName());
		ArmorMaterialDataTable = ArmorMaterialDataTableFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MaterialMetaMapperFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'"));
	if (MaterialMetaMapperFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *MaterialMetaMapperFinder.Object.GetName());
		MaterialMetaMapper = MaterialMetaMapperFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> BladeBasicMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/blade/BladeBasicMaterial.BladeBasicMaterial'"));
	if (BladeBasicMaterialFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *BladeBasicMaterialFinder.Object.GetName());
		BladeBasicMaterial = BladeBasicMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> FullerReinforcedMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/fuller/FullerReinforcedMaterial.FullerReinforcedMaterial'"));
	if (FullerReinforcedMaterialFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *FullerReinforcedMaterialFinder.Object.GetName());
		FullerReinforcedMaterial = FullerReinforcedMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> GuardMakeShiftMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/guard/GuardMakeShiftMaterial.GuardMakeShiftMaterial'"));
	if (GuardMakeShiftMaterialFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *GuardMakeShiftMaterialFinder.Object.GetName());
		GuardMakeShiftMaterial = GuardMakeShiftMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> HiltBasicMaterialFinder(
		TEXT("DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/hilt/HiltBasicMaterial.HiltBasicMaterial'"));
	if (HiltBasicMaterialFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *HiltBasicMaterialFinder.Object.GetName());
		HiltBasicMaterial = HiltBasicMaterialFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> PommelDecorativeMaterialFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/model/sword/pommel/PommelDecorativeMaterial.PommelDecorativeMaterial'"));
	if (PommelDecorativeMaterialFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *PommelDecorativeMaterialFinder.Object.GetName());
		PommelDecorativeMaterial = PommelDecorativeMaterialFinder.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> RegisteredItemsFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'"));
	if (PommelDecorativeMaterialFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *RegisteredItemsFinder.Object.GetName());
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
	BuildModuleManager = NewObject<UBuildModuleManager>(this, UBuildModuleManager::StaticClass());
	CameraManager = NewObject<UCameraManager>(this, UCameraManager::StaticClass());
	RecipeRegistry = NewObject<URecipeRegistry>(this, URecipeRegistry::StaticClass());
	TimeManager = NewObject<UTimeManager>(this, UTimeManager::StaticClass());
	DungeonHandler = NewObject<UNativeDungeonHandler>(this, UNativeDungeonHandler::StaticClass());

	RecipeRegistry->RegistRecipeFromClass();
	TimeManager->StartGlobalTimer();
}

void UCharmingCraftInstance::OnStart()
{
	Super::OnStart();
	//WorldManager->OnLevelLoaded.AddDynamic(GamePlayLogicManager, &UGameEventHandler::OnPlayerJoinEvent);
}
