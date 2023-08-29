// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStack.h"

#include "CharmingCraft/Interface/Meta/HelmetMeta.h"

// Sets default values for this component's properties
UItemStack::UItemStack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
	Material = EMaterial::AIR;
	Amount = 1;
}

UItemStack::UItemStack(const EMaterial Type)
{
	Material = Type;
	Amount = 1;
}

UItemStack::UItemStack(EMaterial Type, int32 Amount)
{
	Material = Type;
	this->Amount = Amount;
}

void UItemStack::PostInitProperties()
{
	UObject::PostInitProperties();
	FString AssetPath = TEXT(
		"/Script/Engine.DataTable'/Game/CharmingCraft/Objects/DataTable/MaterialMetaMapper.MaterialMetaMapper'");
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));

	if (DataTable)
	{
		UEnum* MapperEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMaterial"), true);
		FString MaterialString = MapperEnum->GetNameStringByValue(static_cast<int64>(Material));
		FDMaterial* RowData = DataTable->FindRow<FDMaterial>(FName(MaterialString), TEXT("没找到捏"));

		if (RowData)
		{
			// 使用RowData进行操作
			ItemClass = RowData->ItemClass;
			// TSubclassOf<UItemMeta> ItemMetaClass 只是个类引用 ItemMeta.Class
			ItemMeta = NewObject<UItemMeta>(this, RowData->ItemMeta, "ItemMeta"); // 基于类引用创建对应类型的ItemMeta
		}
	}
}
