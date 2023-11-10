#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../Object/Enum/MaterialType.h"
#include "FBladeBasicMaterial.generated.h"

USTRUCT(BlueprintType)
struct FBladeBasicMaterial : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Material", MakeStructureDefaultValue="None"))
	EMaterial Material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Damage", MakeStructureDefaultValue= 0))
	int32 Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="AttackSpeed", MakeStructureDefaultValue= 0))
	int32 AttackSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Durability", MakeStructureDefaultValue= 0))
	int32 Durability;
};
