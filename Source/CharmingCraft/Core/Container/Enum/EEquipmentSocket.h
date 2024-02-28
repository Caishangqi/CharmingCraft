#pragma once
UENUM(BlueprintType)
enum class EEquipmentSocket: uint8
{
	HEAD UMETA(DisplayName = "Head"),
	BACKPACK UMETA(DisplayName = "Backpack"),
	CLOAK UMETA(DisplayName = "Cloak"),
	HAND UMETA(DisplayName = "Hand"),
	CHEST UMETA(DisplayName = "Chest"),
	LEG UMETA(DisplayName = "Leg"),
	MOUNT UMETA(DisplayName = "Mount")
};
