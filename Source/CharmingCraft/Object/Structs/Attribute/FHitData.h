#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FHitData.generated.h"

USTRUCT(BlueprintType)
struct FHitData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MagicDamage")
	float MagicDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="IsCritic", MakeStructureDefaultValue= true))
	bool IsCritic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CriticalDamage")
	int32 CriticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Instigator")
	APawn* InstigatorPawn;
};
