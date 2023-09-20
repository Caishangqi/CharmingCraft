#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "Engine/DataTable.h"
#include "FDItemStack.generated.h"

USTRUCT(BlueprintType)
struct FDItemStack : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Material", MakeStructureDefaultValue="None"))
	EMaterial Material;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Amount", MakeStructureDefaultValue="None"))
	int32 Amount;
};
