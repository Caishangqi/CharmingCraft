#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FInternalCostume.generated.h"

class UBuffInfo;

USTRUCT(BlueprintType)
struct FInternalCostume : public FTableRowBase
{
	GENERATED_BODY()

	FInternalCostume()
		: id(0)
		  , CostumeName("")
		  , CostumeMaterial(nullptr)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costume ID")
	int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costume Name")
	FName CostumeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costume Material")
	TObjectPtr<UMaterial> CostumeMaterial;
};
