#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FEquipmentAttribute.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentAttribute : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MagicDamage")
	int32 MagicDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Speed", MakeStructureDefaultValue= 0.0f))
	float AttackSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Durability", MakeStructureDefaultValue= 0))
	int32 Durability;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CriticalChance", MakeStructureDefaultValue= 0))
	int32 CriticalChance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CriticalDamage", MakeStructureDefaultValue= 0))
	int32 CriticalDamage;
};
