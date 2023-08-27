#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Interface/ItemMeta.h"
#include "Engine/DataTable.h"
#include "FDMaterial.generated.h"


USTRUCT(BlueprintType)
struct FDMaterial : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Material Registry Name", MakeStructureDefaultValue="None"))
	FString MaterialType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		meta=(DisplayName="Default Texture", MakeStructureDefaultValue="None"))
	TObjectPtr<UTexture2D> DefaultTexture;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
			meta=(DisplayName="ItemMeta", MakeStructureDefaultValue="None"))
	TSubclassOf<UItemMeta> ItemMeta;
};
