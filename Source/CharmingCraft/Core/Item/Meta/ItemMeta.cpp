// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMeta.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"
#include "CharmingCraft/Object/Class/Util/ItemPreviewRender.h"

// Sets default values for this component's properties
UItemMeta::UItemMeta()
{
	bIsRenderItem = false;
}

void UItemMeta::PostInitProperties()
{
	UObject::PostInitProperties();
}

TSharedPtr<FJsonObject> UItemMeta::SerializeToJson()
{
	CREATE_JSON_OBJECT(SerilizeJson);

	TArray<TSharedPtr<FJsonValue>> MetaJsonValues;
	for (const FString& Item : Lore)
	{
		MetaJsonValues.Add(MakeShareable(new FJsonValueString(Item)));
	}
	SET_JSON_FIELD_ARRAY(SerilizeJson, Lore, MetaJsonValues);
	SET_JSON_FIELD_STRING(SerilizeJson, DisplayName, DisplayName);
	SET_JSON_FIELD_NUMBER(SerilizeJson, CustomModelData, CustomModelData);
	SET_JSON_FIELD_NUMBER(SerilizeJson, Durability, Durability);
	SET_JSON_FIELD_BOOL(SerilizeJson, bIsRenderItem, bIsRenderItem);
	return SerilizeJson;
}

UObject* UItemMeta::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	UItemMeta* NewInstance = NewObject<UItemMeta>();
	TArray<TSharedPtr<FJsonValue>> MetaJsonValues = GET_JSON_FIELD_ARRAY(JsonObject, Lore);
	for (auto MetaJsonValue : MetaJsonValues)
	{
		Lore.Add(FString(MetaJsonValue.Get()->AsString()));
	}
	DisplayName = GET_JSON_FIELD_STRING(JsonObject, DisplayName);
	CustomModelData = GET_JSON_FIELD_NUMBER(JsonObject, CustomModelData);
	Durability = GET_JSON_FIELD_NUMBER(JsonObject, Durability);
	bIsRenderItem = GET_JSON_FIELD_BOOL(JsonObject, bIsRenderItem);
	return NewInstance;
}


void UItemMeta::UpdateRender(UWorld* RenderWorld)
{
	// 如果是需要渲染的物品
	if (bIsRenderItem)
	{
		ItemModelMesh->InitResources();
		UMaterialInstanceDynamic* RenderedTexture = DuplicateObject<UMaterialInstanceDynamic>(
			UItemPreviewRender::Get()->RenderItem(this, RenderWorld), this);

		this->DynamicRenderingInstance = RenderedTexture;
	}
}
