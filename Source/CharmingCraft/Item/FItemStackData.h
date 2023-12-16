#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "FItemStackData.generated.h"

USTRUCT(BlueprintType)
/*!
 * This Struct is used for Serialization of ItemStack
 */
struct FItemStackData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Serialization Data")
	int32 Amount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Serialization Data")
	EMaterial Material;
};
