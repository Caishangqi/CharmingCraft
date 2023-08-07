#pragma once
#pragma once
#include "CoreMinimal.h"
#include  "FDSlotStruct.generated.h"

USTRUCT(BlueprintType)
struct FDSlotStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="ItemID"))
	FText ItemID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Quantity"))
	int32 Quantity;
};
