#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Interface/Meta/ItemMeta.h"
#include "Engine/DataTable.h"
#include "../Object/Enum/MaterialType.h"
#include "CharmingCraft/Object/Class/Item/Item.h"
#include "FDMaterial.generated.h"

USTRUCT(BlueprintType)
/* 这是映射表,映射Material和ItemMeta之间的关系 */
struct FDMaterial : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Material", MakeStructureDefaultValue="None"))
	EMaterial Material;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="ItemMeta", MakeStructureDefaultValue="None"))
	TSubclassOf<UItemMeta> ItemMeta;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Color", MakeStructureDefaultValue= NULL))
	FColor Color;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="ItemClass", MakeStructureDefaultValue="None"))
	TSubclassOf<UItem> ItemClass;
};
