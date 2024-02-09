// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistentDataContainer.h"

#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"

TSharedPtr<FJsonObject> UPersistentDataContainer::SerializeToJson()
{
	CREATE_JSON_OBJECT(SerilizeJson);
	return SerilizeJson;
}
