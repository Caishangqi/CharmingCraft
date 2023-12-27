#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "LevelTargetPoint.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ALevelTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TargetName;
};
