#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Save/Data/FSerializeData.h"
#include "UObject/Interface.h"
#include "ISerializable.generated.h"


UINTERFACE()
class USerializable : public UInterface
{
	GENERATED_BODY()
};

class CHARMINGCRAFT_API ISerializable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FString Serialize();

	TSharedPtr<FJsonObject> SerializeToJson();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UObject* Deserialize(const FString& SerializeData);
};
