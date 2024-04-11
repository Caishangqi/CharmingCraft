#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SceneWarpPoint.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ASceneWarpPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	ASceneWarpPoint();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TargetName;
};
