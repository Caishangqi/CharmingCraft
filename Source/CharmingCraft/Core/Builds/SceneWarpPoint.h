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

	virtual void BeginPlay() override;

	bool IsInitialized() const
	{
		return bIsInitialized;
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TargetName;

private:
	bool bIsInitialized = false;
};
