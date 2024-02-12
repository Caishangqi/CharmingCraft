#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISerializable.generated.h"


UINTERFACE()
class USerializable : public UInterface
{
	GENERATED_BODY()

public:
};

class CHARMINGCRAFT_API ISerializable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString Serialize();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UObject* Deserialize(const FString& SerializeData);
};
