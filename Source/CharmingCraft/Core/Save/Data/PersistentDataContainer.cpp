// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistentDataContainer.h"

#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"

TSharedPtr<FJsonObject> UPersistentDataContainer::SerializeToJson()
{
	CREATE_JSON_OBJECT(SerilizeJson);
	return SerilizeJson;
}

UObject* UPersistentDataContainer::Deserialize_Implementation(const FString& SerializeData)
{
	CREATE_JSON_OBJECT_FROM_STRING(DeserializeReader, DeserializeJsonObject, SerializeData);
	return DeserializeFromJson(DeserializeJsonObject);
}

FString UPersistentDataContainer::Serialize_Implementation()
{
	EXPORT_JSON_OBJECT_AND_SERIALIZE(SerializeToJson(), SerilizeString)
	return SerilizeString;
}
