// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Save/Interface/ISerializable.h"
#include "UObject/Object.h"
#include "PersistentDataContainer.generated.h"

/*!
  @author Shangqi Cai 
  The Class indicated the UObject that can be serialize, user need implement
  SerializeToJson(), and DeserializeFromJson() to support UObject serialization
  
  @note Deserialize_Implementation() and Serialize_Implementation() do not need
  override by subclass, it call Native C++ Serialization and return String and Object
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
