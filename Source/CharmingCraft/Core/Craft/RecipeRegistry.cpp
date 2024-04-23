// Fill out your copyright notice in the Description page of Project Settings.


#include "RecipeRegistry.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Recipe/BaseRecipeEntry.h"

bool URecipeRegistry::RegistRecipeFromClass()
{
	// 获取资产注册表模块
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<
		FAssetRegistryModule>("AssetRegistry");

	// 创建一个资产搜索条件
	FARFilter Filter;
	Filter.bRecursivePaths = true; // 搜索子目录
	Filter.bRecursiveClasses = true;
	//Filter.ClassPaths.Add(UBaseRecipeEntry::StaticClass()->GetClassPathName());
	Filter.PackagePaths.Add("/Game/CharmingCraft/Recipe/"); // 指定搜索的根目录

	// 存储找到的资产数据
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	if (AssetData.IsEmpty())
	{
		UE_LOG(LogChamingCraftRecipe, Error,
		       TEXT("[🏷️]  Can not find any Recipe\n"
			       "		Perhaps wrong PackagePaths\n"
			       "		The Recipe path is: %s"), *UBaseRecipeEntry::StaticClass()->GetClassPathName().ToString());
		return false;
	}

	// 遍历所有找到的配方资产
	for (const FAssetData& Asset : AssetData)
	{
		FSoftObjectPath AssetPath = Asset.GetSoftObjectPath();
		UBlueprint* BlueprintAsset = Cast<UBlueprint>(Streamable.LoadSynchronous(AssetPath));

		if (BlueprintAsset && BlueprintAsset->GeneratedClass)
		{
			// 现在获取蓝图生成的类
			UClass* GeneratedClass = BlueprintAsset->GeneratedClass;

			// 确保生成的类是UBaseRecipeEntry的子类
			if (GeneratedClass->IsChildOf(UBaseRecipeEntry::StaticClass()))
			{
				// 现在你可以安全地创建UBaseRecipeEntry的实例或者进行进一步操作
				// 如果你需要创建一个实例，你可以使用NewObject<UBaseRecipeEntry>(...);
				// 如果你只是需要使用它的属性，你可以这样获取它的属性
				UBaseRecipeEntry* RecipeEntryAsset = Cast<UBaseRecipeEntry>(GeneratedClass->GetDefaultObject());
				if (RecipeEntryAsset)
				{
					if (RegistedRecipe.Contains(RecipeEntryAsset->OwnerContainer))
					{
						RegistedRecipe[RecipeEntryAsset->OwnerContainer].ContainerCollection.Add(RecipeEntryAsset);
					}
					else
					{
						RegistedRecipe.Add(RecipeEntryAsset->OwnerContainer, FRecipesContainerCollection());
						RegistedRecipe[RecipeEntryAsset->OwnerContainer].ContainerCollection.Add(RecipeEntryAsset);
					}
					UE_LOG(LogChamingCraftRecipe, Display,
					       TEXT("[🏷️]  Regist Recipe from Asset: %s\n"
						       "		Recipe Namespace: %s\n"
						       "		Recipe Container: %s"), *RecipeEntryAsset->RecipeName,
					       *RecipeEntryAsset->NameSpace.ToString(), *RecipeEntryAsset->OwnerContainer.ToString());
				}
			}
		}
	}

	return true;
}
