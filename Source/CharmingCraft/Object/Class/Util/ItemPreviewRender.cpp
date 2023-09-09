// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPreviewRender.h"
UItemPreviewRender* UItemPreviewRender::Instance = nullptr;

UItemPreviewRender* UItemPreviewRender::Get()
{
	if (!Instance)
	{
		
		Instance = NewObject<UItemPreviewRender>();
		Instance->AddToRoot(); // 防止垃圾回收
	}
	return Instance;
}

void UItemPreviewRender::RenderItem(UItemStack* InputStack)
{
	
}
