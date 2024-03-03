#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Resource/Gather/ResourceEntityGeometryActor.h"
#include "FResourceGeometryData.generated.h"

// #pragma once
// UENUM(BlueprintType)
// enum class EResourceHandleMethods: uint8
// {
// 	DAMAGE UMETA(DisplayName = "Damage"),
// 	BREAK UMETA(DisplayName = "Break")
// };


USTRUCT(BlueprintType)
struct FResourceGeometryData
{
	GENERATED_BODY()

public:
	FResourceGeometryData(): OnDamageGeometry(nullptr), OnBreakGeometry(nullptr)
	{
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry")
	TSubclassOf<AResourceEntityGeometryActor> OnDamageGeometry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Geometry")
	TSubclassOf<AResourceEntityGeometryActor> OnBreakGeometry;
};
