#pragma once
#pragma once
#include "CoreMinimal.h"
#include  "FDSlotStruct.generated.h"

USTRUCT(BlueprintType)
struct FDSlotStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="ItemID"))
	FName ItemID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Quantity"))
	int32 Quantity;

	FDSlotStruct(): ItemID(FName("None")), Quantity(0)
	{
	}
};
