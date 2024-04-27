#pragma once
#include "CoreMinimal.h"
#include "FItemMeta.h"
#include "../Object/Enum/MaterialType.h"
#include "../Object/Class/Item/Item.h"
#include "../Core/Item/Meta/ItemMeta.h"
#include "FItemStack.generated.h"

USTRUCT(BlueprintType)
struct FItemStackData
{
	GENERATED_BODY()

public:
	FItemStackData(): Amount(0), Material(EMaterial::AIR), bCustomizeItemMeta(false), ItemMeta()
	{
	}

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
	bool bCustomizeItemMeta;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	FItemMetaData ItemMeta;
};
