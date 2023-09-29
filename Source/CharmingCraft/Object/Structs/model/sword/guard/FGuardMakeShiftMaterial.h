#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../Object/Enum/MaterialType.h"
#include "FGuardMakeShiftMaterial.generated.h"

USTRUCT(BlueprintType)
struct FGuardMakeShiftMaterial : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Material", MakeStructureDefaultValue="None"))
	EMaterial Material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Damage", MakeStructureDefaultValue= 0))
	int32 Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Speed", MakeStructureDefaultValue= 0))
	int32 Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Durability", MakeStructureDefaultValue= 0))
	int32 Durability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Armor", MakeStructureDefaultValue= 0))
	int32 Armor;
};
