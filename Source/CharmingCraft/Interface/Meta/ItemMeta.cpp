// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMeta.h"

#include "CharmingCraft/Object/Class/Util/ItemPreviewRender.h"

// Sets default values for this component's properties
UItemMeta::UItemMeta()
{
}

void UItemMeta::PostInitProperties()
{
	UObject::PostInitProperties();
}

void UItemMeta::UpdateRender(UWorld* RenderWorld)
{
	// 如果是需要渲染的物品
	if (bIsRenderItem)
	{
		UMaterialInstanceDynamic* RenderedTexture = DuplicateObject<UMaterialInstanceDynamic>(
			UItemPreviewRender::Get()->RenderItem(this, RenderWorld), this);

		this->DynamicRenderingInstance = RenderedTexture;
	}
}
