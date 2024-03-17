#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Resource/DropTable/DropTableData.h"
#include "FCropData.generated.h"

UENUM(BlueprintType)
enum class ETimeUnit : uint8
{
	Seconds,
	Minute,
	Hours,
	Days,
	Weeks,
	Month,
	Years,
};


USTRUCT(BlueprintType, Blueprintable)
struct FCropData
{
	GENERATED_BODY()

public:
	FCropData():TimeUnit(ETimeUnit::Seconds), GrowthMultiplier(0)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CropStageMesh")
	TMap<int32, TObjectPtr<UStaticMesh>> CropStageMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CropStageDrop")
	TMap<int32, TObjectPtr<UDropTableData>> CropStageDrop;

	// <1,100> means the need 100 <units> to fulfill first stage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CropPerStageCount")
	TMap<int32, int32> PerStageCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CropStageTimeUnit")
	ETimeUnit TimeUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CropGrowthMultiplier")
	float GrowthMultiplier;
};
