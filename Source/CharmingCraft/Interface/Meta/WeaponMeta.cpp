// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponMeta.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Util/ItemPreviewRender.h"


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

UAnimMontage* UWeaponMeta::GetCurrentAttackAnimationMontage()
{
	return LoadedAnimMontage[CurrentAttackStage - 1];
}

UObject* UWeaponMeta::Deserialize_Implementation(const FString& SerializeData)
{
	UE_LOG(LogChamingCraftSerilization, Display, TEXT(
		       "[~] UWeaponMeta::Deserialize_Implementation"
	       ))
	return nullptr;
}
