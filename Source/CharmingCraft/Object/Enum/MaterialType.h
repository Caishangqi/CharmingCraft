﻿#pragma once
UENUM(BlueprintType)
enum class EMaterial: uint8
{
	AIR UMETA(DisplayName = "Air"),
	APPLE UMETA(DisplayName = "Apple"),
	CACTUS UMETA(DisplayName = "Cactus"),
	COPPER UMETA(DisplayName = "Copper"),
	LEAD UMETA(DisplayName = "Lead"),
	COBALT UMETA(DisplayName = "Cobalt"),

	// Equipment
	HELMET UMETA(DisplayName = "Helmet"),
	SWORD UMETA(DisplayName = "Sword"),
	PICKAXE UMETA(DisplayName = "Pickaxe"),
	HAND UMETA(DisplayName = "Hand"),
	HOE UMETA(DisplayName = "HOE"),

	// Resource
	ROCKS UMETA(DisplayName = "ROCKS"),
	DEEPSLATE_PIECE UMETA(DisplayName = "DEEPSLATE_PIECE"),
	RUBY UMETA(DisplayName = "RUBY"),

	// Seeds
	CORN_SEED UMETA(DisplayName = "CORN_SEED"),

	// Block
	PLANT_BOX UMETA(DisplayName = "PLANT_BOX"),
	FARM_LAND UMETA(DisplayName = "FARM_LAND"),
	

	// Biome Surface
	BLOCK_MUD UMETA(DisplayName = "BLOCK_MUD"),
	BLOCK_DRIED_MUD UMETA(DisplayName = "BLOCK_DRIED_MUD"),
	BLOCK_GRASS UMETA(DisplayName = "BLOCK_GRASS"),
	BLOCK_STONE UMETA(DisplayName = "BLOCK_STONE")
};
