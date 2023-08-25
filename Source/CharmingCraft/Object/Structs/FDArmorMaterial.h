#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include  "FDArmorMaterial.generated.h"

USTRUCT()
struct FDArmorMaterial : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Tier"))
	FText Tier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Material"))
	FText Material; // 物品系统应当重置,按照Minecraft的设计

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Color"))
	FColor Color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Dimension"))
	FText Dimension;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Type"))
	FText Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Creation"))
	FText Creation;

	/* Attributes */

	/* Plate */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateDurability"))
	int32 PlateDurability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateTotalArmor"))
	int32 PlateTotalArmor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateToughness"))
	int32 PlateToughness;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateKnockResist"))
	float PlateKnockResist;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateTotalMovementSpd"))
	float PlateTotalMovementSpd;
	/* Core */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CoreDurabilityMultiplier"))
	float CoreDurabilityMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CoreArmorMultiplier"))
	float CoreArmorMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CoreMovementSpdMultiplier"))
	float CoreMovementSpdMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CoreChangeMultiplier"))
	float CoreChangeMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CoreProductMultiplier"))
	float CoreProductMultiplier;


	/* Trim */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="TrimDurability"))
	int32 TrimDurability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateTotalArmor"))
	int32 TrimTotalArmor;

	/* Trait */

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Trait"))
	FText Trait;

	/* Texture */

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateTexture"))
	UMaterial* PlateTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CoreTexture"))
	UMaterial* CoreTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="TrimTexture"))
	UMaterial* TrimTexture;
};
