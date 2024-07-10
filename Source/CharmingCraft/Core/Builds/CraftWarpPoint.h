#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "CraftWarpPoint.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ACraftWarpPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	ACraftWarpPoint();

	virtual void BeginPlay() override;

	bool IsInitialized() const
	{
		return bIsInitialized;
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TargetName;

protected:
	UFUNCTION(BlueprintCallable)
	bool SynchronizeDataToCraftWords();
	
private:
	bool bIsInitialized = false;
};
