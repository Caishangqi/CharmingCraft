// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/Item/ItemStack.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"
#include "CharmingCraft/Object/Class/Util/ItemRegistry.h"
#include "CharmingCraft/Object/Structs/FDMaterial.h"

// Sets default values for this component's properties
UItemStack::UItemStack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...
	Material = EMaterial::AIR;
	Amount = 1;
}

UItemStack* UItemStack::Initialize(const EMaterial SetType, const int32 SetAmount)
{
	this->Material = SetType;
	this->Amount = SetAmount;
	SynchronizeData();
	return this;
}


bool UItemStack::SynchronizeData()
{
	//MaterialMetaMapper
	const FString AssetPath = TEXT(
		"/Script/Engine.DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'");
	UDataTable* MaterialMetaMapper = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));


	if (MaterialMetaMapper)
	{
		UEnum* MapperEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMaterial"), true);
		FString MaterialString = MapperEnum->GetNameStringByValue(static_cast<int64>(Material));
		FDMaterial* RowData = MaterialMetaMapper->FindRow<FDMaterial>(FName(MaterialString),
		                                                              TEXT(
			                                                              "[x] Can not find corresponding material from MaterialMetaMapper DataTable"));
		if (RowData)
		{
			// TSubclassOf<UItemMeta> ItemMetaClass 只是个类引用 ItemMeta.Class
			this->ItemMeta = NewObject<UItemMeta>(this, RowData->ItemMeta, FName(RowData->ItemMeta->GetName()));
			// 基于类引用创建对应类型的ItemMeta
			this->ItemClass = RowData->ItemClass;
			this->ItemMeta->DisplayName = ItemClass.GetDefaultObject()->DisplayName.ToString();
			return true;
		}
	}

	return false;
}

void UItemStack::PostInitProperties()
{
	Super::PostInitProperties();
	//在这里调用ItemMap[Material]是空的，因为生命周期相同时刻
	SynchronizeData();
}

UItem* UItemStack::GetItemClass() const
{
	return ItemClass.GetDefaultObject();
}

TSharedPtr<FJsonObject> UItemStack::SerializeToJson()
{
	CREATE_JSON_OBJECT(SerilizeJson);
	SET_JSON_FIELD_NUMBER(SerilizeJson, Amount, Amount);
	SET_JSON_FIELD_ENUM(SerilizeJson, Material, EMaterial, Material);
	SET_JSON_FIELD_OBJECT(SerilizeJson, ItemMeta, ItemMeta->SerializeToJson());
	return SerilizeJson;
}

UObject* UItemStack::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	UItemStack* NewInstance = NewObject<UItemStack>();
	INJECT_JSON_FIELD_ENUM(JsonObject, Material, EMaterial, NewInstance->Material);
	NewInstance->Amount = GET_JSON_FIELD_NUMBER(JsonObject, Amount);

	const TSharedPtr<FJsonObject> FItemMetaJsonObject = GET_JSON_FIELD_OBJECT(JsonObject, ItemMeta);
	// Ensure ItemMeta Class
	const TSubclassOf<UItemMeta> JsonConvertItemMetaClass = GET_CLASS_FROM_STRING(
		GET_JSON_FIELD_STRING(FItemMetaJsonObject,Class));
	// Call Class Specific Deserialize method
	NewInstance->ItemMeta = Cast<UItemMeta>(
		JsonConvertItemMetaClass.GetDefaultObject()->DeserializeFromJson(FItemMetaJsonObject)
	);
	return NewInstance;
}

UItemStack* UItemStack::CopyData()
{
	UItemStack* NewInstance = NewObject<UItemStack>();
	NewInstance->Material = this->Material;
	NewInstance->ItemClass = this->ItemClass;
	NewInstance->Amount = this->Amount;
	NewInstance->ItemMeta = DuplicateObject<UItemMeta>(this->ItemMeta, this);
	return NewInstance;
}
