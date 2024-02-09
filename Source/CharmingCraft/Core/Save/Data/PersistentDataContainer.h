// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PersistentDataContainer.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPersistentDataContainer : public UObject
{
	GENERATED_BODY()

public:
	virtual TSharedPtr<FJsonObject> SerializeToJson();

	virtual UObject * DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
	{
		return nullptr;
	}
};
