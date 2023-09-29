#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../Object/Enum/MaterialType.h"
#include "FPommelDecorativeMaterial.generated.h"

USTRUCT(BlueprintType)
struct FPommelDecorativeMaterial : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Material", MakeStructureDefaultValue="None"))
	EMaterial Material;

};
