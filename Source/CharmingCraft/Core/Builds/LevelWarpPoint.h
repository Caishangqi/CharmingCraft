#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "LevelWarpPoint.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ALevelWarpPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	ALevelWarpPoint();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TargetName;
};
