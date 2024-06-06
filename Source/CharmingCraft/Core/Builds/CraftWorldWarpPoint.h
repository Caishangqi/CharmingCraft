#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "CraftWorldWarpPoint.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ACraftWorldWarpPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	ACraftWorldWarpPoint();

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
