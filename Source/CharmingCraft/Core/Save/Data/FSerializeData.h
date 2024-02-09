#pragma once
#include "CoreMinimal.h"
#include "FSerializeData.generated.h"

USTRUCT(BlueprintType)
struct FSerializeData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UObject> SerializeClassName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, FString> Attributes;
};
