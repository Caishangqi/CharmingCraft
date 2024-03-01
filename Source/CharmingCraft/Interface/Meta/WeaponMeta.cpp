// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponMeta.h"

#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"


bool UWeaponMeta::AssembleComponent(AActor* Actor)
{
	return false;
}


TSharedPtr<FJsonObject> UWeaponMeta::SerializeToJson()
{
	TSharedPtr<FJsonObject> ItemWeaponMetaJsonObject = Super::SerializeToJson();
	CREATE_JSON_OBJECT(WeaponAttributeJsonObject);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Damage, EquipmentAttribute.Damage);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, MagicDamage, EquipmentAttribute.MagicDamage);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, AttackSpeed, EquipmentAttribute.AttackSpeed);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Durability, EquipmentAttribute.Durability);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalChance, EquipmentAttribute.CriticalChance);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalDamage, EquipmentAttribute.CriticalDamage);
	// Put WeaponJsonObject into BaseItemMetaJsonObject
	SET_JSON_FIELD_OBJECT(ItemWeaponMetaJsonObject, WeaponAttribute, WeaponAttributeJsonObject);
	SET_JSON_FIELD_NUMBER(ItemWeaponMetaJsonObject, CurrentAttackStage, CurrentAttackStage);
	return ItemWeaponMetaJsonObject;
}

UObject* UWeaponMeta::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	UWeaponMeta* WeaponMeta = Cast<UWeaponMeta>(Super::DeserializeFromJson(JsonObject));
	CurrentAttackStage = GET_JSON_FIELD_NUMBER(JsonObject, CurrentAttackStage);
	// Deserialize WeaponAttribute From WeaponAttributeJsonObject
	const TSharedPtr<FJsonObject> WeaponAttributeJsonObject = GET_JSON_FIELD_OBJECT(JsonObject, WeaponAttribute);
	EquipmentAttribute.Damage = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Damage);
	EquipmentAttribute.MagicDamage = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, MagicDamage);
	EquipmentAttribute.AttackSpeed = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, AttackSpeed);
	EquipmentAttribute.Durability = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Durability);
	EquipmentAttribute.CriticalChance = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalChance);
	EquipmentAttribute.CriticalDamage = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalDamage);
	return WeaponMeta;
}
