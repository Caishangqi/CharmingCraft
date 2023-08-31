// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRegistry.h"

#include "CharmingCraft/Object/Class/Item/Item.h"
#include "CharmingCraft/Object/Structs/FDMaterial.h"
#include "Engine/DataTable.h"

UItemRegistry* UItemRegistry::Instance = nullptr;

UItemRegistry* UItemRegistry::Get()
{
	if (!Instance)
	{
		Instance = NewObject<UItemRegistry>();
		Instance->AddToRoot(); // 防止垃圾回收
		Instance->InitializeRegistry();
	}
	return Instance;
}

void UItemRegistry::InitializeRegistry()
{
	// 为每种EMaterial创建一个UItem实例并添加到ItemMap中
	// 例如：

	const FString AssetPath = TEXT(
		"/Script/Engine.DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'");
	UDataTable* MaterialMetaMapper = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));

	if (MaterialMetaMapper)
	{
		TArray<FName> RowNames = MaterialMetaMapper->GetRowNames();

		for (FName RowName : RowNames)
		{
			// 获取每一行的Struct
			FDMaterial* RowStruct = MaterialMetaMapper->FindRow<FDMaterial>(RowName, TEXT("Description"));

			if (RowStruct)
			{
				// 在这里处理RowStruct和RowName
				UE_LOG(LogTemp, Warning, TEXT("UItemRegistry::InitializeRegistry() Material: %s ItemClass: %s"),
				       *RowName.ToString(), *RowStruct->ItemClass->GetName());
				UItem* Item = NewObject<UItem>(this, RowStruct->ItemClass);
				ItemMap.Add(RowStruct->Material, Item);
			}
		}
	}
}
