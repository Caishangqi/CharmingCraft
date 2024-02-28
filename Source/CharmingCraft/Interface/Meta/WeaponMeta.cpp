// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponMeta.h"

#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"
#include "CharmingCraft/Object/Class/Util/ItemPreviewRender.h"
#include "CharmingCraft/Object/Structs/model/EquipmentComponentAnimation.h"


bool UWeaponMeta::AssembleComponent(AActor* Actor)
{
	return false;
}

void UWeaponMeta::UpdateRender(UWorld* RenderWorld)
{
	UMaterialInstanceDynamic* RenderedTexture = DuplicateObject<UMaterialInstanceDynamic>(
		UItemPreviewRender::Get()->RenderItem(this, RenderWorld), this);

	this->DynamicRenderingInstance = RenderedTexture;
}

FAttackStageAnimation UWeaponMeta::GetCurrentAttackAnimationMontage()
{
	return LoadedAnimMontage->AttackStageAnimations[CurrentAttackStage - 1];
}

TSharedPtr<FJsonObject> UWeaponMeta::SerializeToJson()
{
	TSharedPtr<FJsonObject> ItemWeaponMetaJsonObject = Super::SerializeToJson();
	CREATE_JSON_OBJECT(WeaponAttributeJsonObject);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Damage, WeaponAttribute.Damage);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, MagicDamage, WeaponAttribute.MagicDamage);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, AttackSpeed, WeaponAttribute.AttackSpeed);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Durability, WeaponAttribute.Durability);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalChance, WeaponAttribute.CriticalChance);
	SET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalDamage, WeaponAttribute.CriticalDamage);
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
	WeaponAttribute.Damage = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Damage);
	WeaponAttribute.MagicDamage = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, MagicDamage);
	WeaponAttribute.AttackSpeed = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, AttackSpeed);
	WeaponAttribute.Durability = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, Durability);
	WeaponAttribute.CriticalChance = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalChance);
	WeaponAttribute.CriticalDamage = GET_JSON_FIELD_NUMBER(WeaponAttributeJsonObject, CriticalDamage);
	return WeaponMeta;
}
