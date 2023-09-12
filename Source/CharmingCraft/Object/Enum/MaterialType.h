#pragma once
UENUM(BlueprintType)
enum class EMaterial: uint8
{
	AIR UMETA(DisplayName = "Air"),
	APPLE UMETA(DisplayName = "Apple"),
	STONE UMETA(DisplayName = "Stone"),
	CACTUS UMETA(DisplayName = "Cactus"),
	HELMET UMETA(DisplayName = "Helmet")
	// ... 其他材料
};
