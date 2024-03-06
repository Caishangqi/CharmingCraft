#pragma once
#include "CoreMinimal.h"
#include "FPlaceValidation.generated.h"

UENUM(BlueprintType)
enum class EBuildCollidedType: uint8
{
	VALID UMETA(DisplayName = "Valid"),
	COLLIDED UMETA(DisplayName = "Collided"),
	WARNING UMETA(DisplayName = "Warning"),
};


USTRUCT(BlueprintType)
struct FPlaceValidation
{
	GENERATED_BODY()
	FPlaceValidation(): CurrentCollidedType(EBuildCollidedType::VALID), bIsAllowToInteract(false), bIsHighlighted(false)
	{
	}

public:
	UPROPERTY(BlueprintReadWrite)
	EBuildCollidedType CurrentCollidedType;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> ColliedMaterial;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> ValidMaterial;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> WarningMaterial;

	// Document Block Interact Data
	// Useful when Temperately Disable Block Interaction When in building mode
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	bool bIsAllowToInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Visiability")
	bool bIsHighlighted;
};
