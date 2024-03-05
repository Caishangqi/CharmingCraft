#pragma once
UENUM(BlueprintType)
enum class EPlayerMode: uint8
{
	DEFAULT UMETA(DisplayName = "Default"),
	COMBAT UMETA(DisplayName = "Combat"),
	INVENTORY UMETA(DisplayName = "Inventory"),
	BUILD UMETA(DisplayName = "Build")
};
