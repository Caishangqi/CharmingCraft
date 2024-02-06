#pragma once
#include "CoreMinimal.h"
#include "FItemMeta.h"
#include "FItemStack.generated.h"

USTRUCT(BlueprintType)
struct FItemStack
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	int32 Amount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	EMaterial Material; //
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ItemStack Fields")
	TSubclassOf<UItem> ItemClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	TSubclassOf<UItemMeta> ItemMetaClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	FItemMeta ItemMeta;
};
