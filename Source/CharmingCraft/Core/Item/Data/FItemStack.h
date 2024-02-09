#pragma once
#include "CoreMinimal.h"
#include "FItemMeta.h"
#include "../Object/Enum/MaterialType.h"
#include "../Object/Class/Item/Item.h"
#include "../Core/Item/Meta/ItemMeta.h"
#include "CharmingCraft/Core/Save/Data/FSerializeData.h"
#include "FItemStack.generated.h"

USTRUCT(BlueprintType)
struct FItemStackData : public FSerializeData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	int32 Amount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	EMaterial Material; //
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ItemStack Fields")
	TSubclassOf<UItem> ItemClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	TSubclassOf<UItemMeta> ItemMetaClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	FItemMetaData ItemMeta;
};
