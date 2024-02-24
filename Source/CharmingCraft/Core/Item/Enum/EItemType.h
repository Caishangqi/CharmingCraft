#pragma once
UENUM(BlueprintType)
enum class EItemType: uint8
{
	EQUIPMENT UMETA(DisplayName = "Equipment"),
	RESOURCE UMETA(DisplayName = "Resource"),
	MATERIAL UMETA(DisplayName = "Material"),
	CONSUME UMETA(DisplayName = "Consume"),
	FURNITURE UMETA(DisplayName = "furniture")
};
