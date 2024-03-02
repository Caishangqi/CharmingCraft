// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/Item/ItemStack.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"
#include "CharmingCraft/Object/Class/Util/ItemRegistry.h"
#include "CharmingCraft/Object/Structs/FDMaterial.h"
#include "RenderActor/ItemEntityActor.h"
// Sets default values for this component's properties
UItemStack::UItemStack()
{
	Amount = 1;
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

UItemStack* UItemStack::CreateItemStackFromMaterial(UObject* Outer, const EMaterial ItemMaterial, const int32 SetAmount)
{
	/*!
	 *	WARNNING: The outer should be Inventory/Something else when create ItemStack, fail / incorrect assign outer
	 *	will cause serious implicit bug
	 */

	TObjectPtr<UItemStack> ItemStack = NewObject<UItemStack>(Outer, StaticClass());
	ItemStack->Material = ItemMaterial;
	//MaterialMetaMapper
	const FString AssetPath = TEXT(
		"/Script/Engine.DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'");
	UDataTable* MaterialMetaMapper = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));


	if (MaterialMetaMapper)
	{
		UEnum* MapperEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMaterial"), true);
		FString MaterialString = MapperEnum->GetNameStringByValue(static_cast<int64>(ItemMaterial));
		FDMaterial* RowData = MaterialMetaMapper->FindRow<FDMaterial>(FName(MaterialString),
		                                                              TEXT(
			                                                              "[x] Can not find corresponding material from MaterialMetaMapper DataTable"));
		if (RowData)
		{
			TSubclassOf<UItemMeta> ItemMetaClass = RowData->ItemClass.GetDefaultObject()->ItemMetaClass;
			ItemStack->ItemClass = RowData->ItemClass;
			UItem* ItemClass = ItemStack->ItemClass.GetDefaultObject();

			/*!
			 *	WARNNING: The outer should be ItemStack when create ItemMeta, fail / incorrect assign outer
			 *	will cause serious implicit bug
			 */

			ItemStack->ItemMeta = NewObject<UItemMeta>(ItemStack, ItemMetaClass, FName(RowData->ItemMeta->GetName()));
			ItemStack->ItemMeta->DisplayName = ItemClass->DisplayName.ToString();
			if (ItemClass->DefaultItemEntityActorClass)
			{
				ItemStack->ItemMeta->ItemEntityActorClass = ItemClass->DefaultItemEntityActorClass;
			}
			if (ItemClass->MaxStackSize < SetAmount)
			{
				ItemStack->Amount = ItemClass->MaxStackSize;
			}
			else
			{
				ItemStack->Amount = SetAmount;
			}
			// UE_LOG(LogChamingCraftSave, Display, TEXT("[🔍] ItemDisplayName is: %s Container is: %s"),
			//        *ItemStack->ItemMeta->DisplayName, *Outer->GetName());

			return ItemStack;
		}
	}
	return nullptr;
}

UItemStack* UItemStack::CreateItemStackFromItemClass(UObject* Outer, TSubclassOf<UItem> ItemClassName,
                                                     const int32 SetAmount)
{
	TObjectPtr<UItemStack> ItemStack = NewObject<UItemStack>(Outer, StaticClass());
	ItemStack->ItemClass = ItemClassName;
	ItemStack->Material = Cast<UItem>(ItemClassName.GetDefaultObject())->Material;
	ItemStack->ItemMeta = NewObject<UItemMeta>(ItemStack, ItemStack->ItemClass.GetDefaultObject()->ItemMetaClass,
	                                           FName(ItemStack->ItemClass.GetDefaultObject()->ItemMetaClass->
	                                                            GetName()));
	ItemStack->ItemMeta->DisplayName = ItemStack->ItemClass.GetDefaultObject()->DisplayName.ToString();
	return ItemStack;
}
