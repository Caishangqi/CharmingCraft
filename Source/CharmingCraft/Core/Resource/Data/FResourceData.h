#pragma once
#include "CoreMinimal.h"
#include "FResourceData.generated.h"

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_BODY()

public:
	FResourceData(): MaxHeath(10), CurrentHeath(10), ResetHeath(true), ResetHealthTime(4), MinimumGatherValue(0)
	{
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource")
	FName ResourceDataName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource")
	int32 MaxHeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource")
	int32 CurrentHeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource")
	bool ResetHeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource")
	int32 ResetHealthTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource")
	int32 MinimumGatherValue; // Base on EResourceType
};
