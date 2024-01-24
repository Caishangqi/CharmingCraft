#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Damage/EDamageResponse.h"
#include "Engine/DataTable.h"
#include "FHitData.generated.h"

class UBuffInfo;
USTRUCT(BlueprintType)
struct FHitData : public FTableRowBase
{
	GENERATED_BODY()

	FHitData()
		: Damage(0.f)
		  , MagicDamage(0.f)
		  , TrueDamage(0.f)
		  , IsCritic(false)
		  , CriticalDamage(0)
		  , InstigatorPawn(nullptr)
		  , DamageResponse(EDamageResponse::HitReaction) // 设置默认值
		  , OnHitBuffList()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MagicDamage")
	float MagicDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TrueDamage")
	float TrueDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="IsCritic", MakeStructureDefaultValue= true))
	bool IsCritic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CriticalDamage")
	int32 CriticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Instigator")
	APawn* InstigatorPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DamageResponse")
	EDamageResponse DamageResponse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuffList")
	TArray<UBuffInfo*> OnHitBuffList;
};
