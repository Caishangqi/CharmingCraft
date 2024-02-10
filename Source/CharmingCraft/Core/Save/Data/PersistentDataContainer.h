// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Save/Interface/ISerializable.h"
#include "UObject/Object.h"
#include "PersistentDataContainer.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPersistentDataContainer : public UObject, public ISerializable
{
	GENERATED_BODY()

public:
	// Native C++ Serialization
	virtual TSharedPtr<FJsonObject> SerializeToJson();

	virtual UObject* DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
	{
		return nullptr;
	}

	// Unreal BluePrint Serialization Interface Implementation
	virtual UObject* Deserialize_Implementation(const FString& SerializeData) override;
	virtual FString Serialize_Implementation() override;
};
