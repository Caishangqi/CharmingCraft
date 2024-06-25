// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMeta.h"

#include "../Core/Skill/Actions/NativeAction.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Skill/EquipmentSkill/ItemDynamicSkill.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"
#include "CharmingCraft/Core/Skill/Actions/NativeItemAction.h"
#include "../Core/CharmingCraftInstance.h"
#include "Kismet/GameplayStatics.h"

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

bool UItemMeta::AddActionToBindItemSkill(APawn* Instigator, UNativeAction* FromAction, UNativeAction* TargetAction,
                                         UItemMeta* ContextMeta)
{
	// Need to check Empty, fail to check will cause Find() found nullptr
	if (BindItemDynamicSkill.IsEmpty())
	{
		if (Instigator != nullptr)
		{
			// Broadcast ItemDynamicSkillBindEvent
			Cast<UCharmingCraftInstance>(Instigator->GetGameInstance())->GetGameEventHandler()->
			                                                             OnItemDynamicSkillBindEvent(
				                                                             Instigator, nullptr, TargetAction,
				                                                             ContextMeta);
		}
		BindItemDynamicSkill.Add(TargetAction->SkillType, TargetAction);
		return true;
	}

	TObjectPtr<UGameEventHandler> EventHandler;
	if (Instigator != nullptr)
	{
		EventHandler = Cast<UCharmingCraftInstance>(Instigator->GetGameInstance())->
			GetGameEventHandler();
	}


	TObjectPtr<UNativeAction> BindAction = nullptr;
	if (BindItemDynamicSkill.Contains(TargetAction->SkillType))
	{
		BindAction = BindItemDynamicSkill.Find(TargetAction->SkillType)->Get();
	}
	if (!BindAction) // Another check
	{
		if (Instigator != nullptr)
		{
			EventHandler->OnItemDynamicSkillBindEvent(Instigator, BindAction, TargetAction, ContextMeta);
		}
		BindItemDynamicSkill.Add(TargetAction->SkillType, TargetAction);
		return true;
	}

	// If bind repeat, return false
	if (BindAction == TargetAction)
	{
		return false;
	}
	else
	{
		if (Instigator != nullptr)
		{
			EventHandler->OnItemDynamicSkillBindEvent(Instigator, BindAction, TargetAction, ContextMeta);
		}
		BindItemDynamicSkill.Add(TargetAction->SkillType, TargetAction);
		return true;
	}
}

AItemEntityActor* UItemMeta::CreateItemEntityActor(const UObject* WorldContextObject, AActor* Owner)
{
	FTransform DefaultTransform;
	TObjectPtr<AItemEntityActor> AttachedActor = Cast<AItemEntityActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(WorldContextObject, this->ItemEntityActorClass,
		                                                   DefaultTransform,
		                                                   ESpawnActorCollisionHandlingMethod::Undefined, Owner));
	UGameplayStatics::FinishSpawningActor(AttachedActor, DefaultTransform);
	//ItemEntityActor = AttachedActor;
	return AttachedActor;
}

void UItemMeta::InitializeItemMetaData(UItem* ItemClass)
{
	DisplayName = ItemClass->DisplayName.ToString();
	if (ItemClass->DefaultItemEntityActorClass)
	{
		ItemEntityActorClass = ItemClass->DefaultItemEntityActorClass;
	}
}
