// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Object/Class/Util/ItemPreviewRender.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemEntityUtilityLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "ItemEntityUtilityLibrary"))
class CHARMINGCRAFT_API UItemEntityUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Render")
	static void SetItem2DIconFromItemEntity(UItemStack* TargetItemStack, UWorld* RenderWorld)
	{
		if (TargetItemStack != nullptr && TargetItemStack->ItemMeta->bIsRenderItem)
		{
			TObjectPtr<UItemMeta> ItemMeta = TargetItemStack->ItemMeta;
			//ItemMeta->ItemModelMesh->InitResources();
			UMaterialInstanceDynamic* RenderedTexture = DuplicateObject<UMaterialInstanceDynamic>(
				UItemPreviewRender::Get()->RenderItem(ItemMeta, RenderWorld), ItemMeta);
			ItemMeta->DynamicRenderingInstance = RenderedTexture;
			
		}
	};
};
