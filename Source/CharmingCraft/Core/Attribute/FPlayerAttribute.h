#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FPlayerAttribute.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAttribute : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes")
	float Damage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float AbilityPower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float HealthMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Mana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 Level;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float CurrentLevelXP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 KnockBackResistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 CriticalChance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 CriticalDamageEnhance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int CriticalDamageDefenseEnhance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float AttackSpeedEnhance;

	/* Defense */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 Armour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float DamageReducePhysicalDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 MagicDefense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float DamageReduceMagicalDamage;
};
