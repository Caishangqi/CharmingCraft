#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "FWeaponMaterial.generated.h"

USTRUCT()
struct FWeaponMaterial
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Tier", MakeStructureDefaultValue="None"))
	FString Tier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Material", MakeStructureDefaultValue="None"))
	EMaterial Material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Color", MakeStructureDefaultValue= NULL))
	FColor Color;

	/* Attributes */

	/* Weapon Mel*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateDurability", MakeStructureDefaultValue= 0))
	int32 Blade;

	// TODO 仔细设计这里的数值
};
