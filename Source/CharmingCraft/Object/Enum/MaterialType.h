#pragma once
UENUM(BlueprintType)
enum class EMaterial: uint8
{
	AIR UMETA(DisplayName = "Air"),
	APPLE UMETA(DisplayName = "Apple"),
	CACTUS UMETA(DisplayName = "Cactus"),
	COPPER UMETA(DisplayName = "Copper"),
	LEAD UMETA(DisplayName = "Lead"),
	COBALT UMETA(DisplayName = "Cobalt"),
	HELMET UMETA(DisplayName = "Helmet"),
	SWORD UMETA(DisplayName = "Sword"),
	PICKAXE UMETA(DisplayName = "Pickaxe"),
	HAND UMETA(DisplayName = "Hand"),

	// Block
	PLANT_BOX UMETA(DisplayName = "Plant Box"),


	// Biome Surface
	MUD UMETA(DisplayName = "MUD"),
	DRIED_MUD UMETA(DisplayName = "DRIED_MUD"),
	GRASS UMETA(DisplayName = "GRASS"),
	STONE UMETA(DisplayName = "STONE")
};
