// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveManager.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "Kismet/GameplayStatics.h"

UGameSaveManager::UGameSaveManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> InternalCostumeFinder(
		TEXT(
			"DataTable'/Game/CharmingCraft/Save/InternalCostumeSet.InternalCostumeSet'"));
	if (InternalCostumeFinder.Succeeded())
	{
		InternalCostume = InternalCostumeFinder.Object;
	}

	UpdateSaveSlots();
}

bool UGameSaveManager::SaveGameToFile(const FString& SaveSlotName)
{
	return true;
}

bool UGameSaveManager::LoadGameFromFile(const FString& SaveSlotName)
{
	return true;
}

bool UGameSaveManager::DoesSaveGameExist(const FString& SaveSlotName)
{
	return true;
}

//UE_LOG(LogChamingCraftSave, Display, TEXT("[+] Unable Load Save: %s"), *SaveFilePath);
void UGameSaveManager::UpdateSaveSlots()
{
	IFileManager& FileManager = IFileManager::Get();
	FString SaveGamesDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames");

	TArray<FString> RequiredFiles = {
		TEXT("PlayerData.sav"), TEXT("RealmData.sav"), TEXT("ProgressData.sav"), TEXT("LevelData.sav")
	};

	// 这个lambda函数将被调用每次一个文件或目录被找到
	FileManager.IterateDirectory(*SaveGamesDirectory,
	                             [this,&RequiredFiles, &FileManager](const TCHAR* FilenameOrDirectory,
	                                                                 bool bIsDirectory) -> bool
	                             {
		                             // 只对目录感兴趣
		                             if (bIsDirectory)
		                             {
			                             FString FullPath(FilenameOrDirectory);

			                             TArray<FString> FoundFiles;
			                             FileManager.FindFiles(FoundFiles, *FullPath, *FString(".sav"));

			                             // 输出调试信息
			                             UE_LOG(LogChamingCraftSave, Display, TEXT("[🔍] Searching in: %s"), *FullPath);
			                             for (FString& File : FoundFiles)
			                             {
				                             UE_LOG(LogChamingCraftSave, Display, TEXT("[📄] Found file: %s"), *File);
			                             }

			                             // 检查是否所有必要文件都存在
			                             bool bIsValid = true;
			                             for (FString& RequiredFile : RequiredFiles)
			                             {
				                             if (!FoundFiles.Contains(RequiredFile))
				                             {
					                             bIsValid = false;
					                             break;
				                             }
			                             }

			                             // 如果当前目录包含所有必要文件，则认为是一个有效的存档
			                             if (bIsValid)
			                             {
				                             FSaveSlotInfo SaveSlotInfo;
				                             // 从完整路径中提取目录名称

				                             FString DirName = FPaths::GetCleanFilename(FullPath);
				                             SaveSlotInfo.SaveSlotName = DirName;
				                             SaveSlotInfo.SaveSlotPath = FullPath;
				                             SaveSlotInfo.SaveSlotID = 0;
				                             ValidSaveSlots.Add(SaveSlotInfo);
				                             UE_LOG(LogChamingCraftSave, Display, TEXT("[⨠] Load Save: %s"), *DirName);
			                             }
		                             }

		                             // 返回true以继续迭代
		                             return true;
	                             });
}


void UGameSaveManager::InitializeNewSaveGame()
{
}

bool UGameSaveManager::PerformSaveGameToFile(const FSaveSlotInfo& SaveSlotName)
{
	UGameplayStatics::SaveGameToSlot(SaveSlotName.PlayerData, SaveSlotName.SaveSlotName + "/" + FString("PlayerData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("[📥] Save 1 files %s to Save Slot: %s"), *FString("PlayerData.sav"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.RealmData, SaveSlotName.SaveSlotName + "/" + FString("RealmData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("[📥] Save 1 files %s to Save Slot: %s"), *FString("RealmData.sav"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.ProgressData,
	                                 SaveSlotName.SaveSlotName + "/" + FString("ProgressData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("[📥] Save 1 files %s to Save Slot: %s"), *FString("ProgressData.sav"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.LevelData,
	                                 SaveSlotName.SaveSlotName + "/" + FString("LevelData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("[📥] Save 1 files %s to Save Slot: %s"), *FString("LevelData.sav"),
	       *SaveSlotName.SaveSlotName);

	UpdateSaveSlots();
	PerformLoadGameFromFile();
	return true;
}

void UGameSaveManager::PerformLoadGameFromFile()
{
	if (ValidSaveSlots.Num() != 0)
	{
		for (auto& SaveSlotName : ValidSaveSlots)
		{
			if (!IsValid(SaveSlotName.PlayerData))
			{
				SaveSlotName.PlayerData = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(
					SaveSlotName.SaveSlotName + "/" + FString("PlayerData"),
					0));
				SaveSlotName.LevelData = Cast<ULevelData>(UGameplayStatics::LoadGameFromSlot(
					SaveSlotName.SaveSlotName + "/" + FString("LevelData"),
					0));
				SaveSlotName.ProgressData = Cast<UProgressData>(UGameplayStatics::LoadGameFromSlot(
					SaveSlotName.SaveSlotName + "/" + FString("ProgressData"),
					0));
				SaveSlotName.RealmData = Cast<URealmData>(UGameplayStatics::LoadGameFromSlot(
					SaveSlotName.SaveSlotName + "/" + FString("RealmData"),
					0));
			}
		}
	}
}
