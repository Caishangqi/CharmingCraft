#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include  "FDArmorMaterial.generated.h"

USTRUCT()
struct FDArmorMaterial : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Tier", MakeStructureDefaultValue="None"))
	FString Tier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Material", MakeStructureDefaultValue="None"))
	EMaterial Material; // 物品系统应当重置,按照Minecraft的设计

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Color", MakeStructureDefaultValue= NULL))
	FColor Color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Dimension", MakeStructureDefaultValue="None"))
	FString Dimension;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Type", MakeStructureDefaultValue="None"))
	FString Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Creation", MakeStructureDefaultValue= "None"))
	FString Creation;

	/* Attributes */

	/* Plate */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateDurability", MakeStructureDefaultValue= 0))
	int32 PlateDurability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateTotalArmor", MakeStructureDefaultValue= 0))
	int32 PlateTotalArmor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateToughness", MakeStructureDefaultValue= 0))
	int32 PlateToughness;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateKnockResist", MakeStructureDefaultValue= 0.0f))
	float PlateKnockResist;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="PlateTotalMovementSpd", MakeStructureDefaultValue= 0.0f))
	float PlateTotalMovementSpd;
	/* Core */
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="CoreDurabilityMultiplier", MakeStructureDefaultValue= 0.0f))
	float CoreDurabilityMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="CoreArmorMultiplier", MakeStructureDefaultValue= 0.0f))
	float CoreArmorMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="CoreMovementSpdMultiplier", MakeStructureDefaultValue= 0.0f))
	float CoreMovementSpdMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="CoreChangeMultiplier", MakeStructureDefaultValue= 0.0f))
	float CoreChangeMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="CoreProductMultiplier", MakeStructureDefaultValue= 0.0f))
	float CoreProductMultiplier;


	/* Trim */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="TrimDurability", MakeStructureDefaultValue= 0))
	int32 TrimDurability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateTotalArmor", MakeStructureDefaultValue= 0))
	int32 TrimTotalArmor;

	/* Trait */

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Trait", MakeStructureDefaultValue="None"))
	FString Trait;

	/* Texture */

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="PlateTexture"))
	UMaterial* PlateTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CoreTexture"))
	UMaterial* CoreTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="TrimTexture"))
	UMaterial* TrimTexture;
};
