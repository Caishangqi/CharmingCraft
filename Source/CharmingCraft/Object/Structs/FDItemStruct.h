#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include  "FDItemStruct.generated.h"

USTRUCT(BlueprintType)
/* 这东西得继承FTable数据表才能在数据表里显示, 逆天 */
struct FDItemStruct : public FTableRowBase

{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Name"))
	FText Name;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Description"))
	FText Description;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Thumbnail", MakeStructureDefaultValue="None"))
	TObjectPtr<UTexture2D> Thumbnail;

	/** We use class reference because if it do not exist yet, if it
	 * is present in the world, then you want to use object reference */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="ItemClass", MakeStructureDefaultValue="None"))
	TObjectPtr<UClass> ItemClass;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="StackSize"))
	int32 StackSize = 64;
};
