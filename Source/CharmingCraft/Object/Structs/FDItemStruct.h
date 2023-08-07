#pragma once
#include "CoreMinimal.h"
#include  "FDItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FDItemStruct
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

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="ItemClass", MakeStructureDefaultValue="None"))
	TObjectPtr<UClass> ItemClass;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="StackSize"))
	int32 StackSize;
};
