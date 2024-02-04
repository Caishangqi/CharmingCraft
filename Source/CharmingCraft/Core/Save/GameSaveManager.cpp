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

	/* Initialize Boundary Slot */
	FSaveSlotInfo BoundarySlot;
	CurrentSaveNode = &BoundarySlot;
	CurrentSaveNode->IsIndicateBound = true;
	ValidSaveSlotsRing.AddHead(*CurrentSaveNode);
	CurrentSaveNode = &ValidSaveSlotsRing.GetHead()->GetValue();

	/* End Initialize Boundary Slot */

	UpdateSaveSlots();
	PerformLoadGameFromFile();
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
				                             UE_LOG(LogChamingCraftSave, Display, TEXT("	[📄] Found file: %s"), *File);
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
				                             // DLL
				                             ValidSaveSlotsRing.AddTail(SaveSlotInfo);


				                             UE_LOG(LogChamingCraftSave, Display, TEXT("		[📤] Load Save: %s"),
				                                    *DirName);
			                             }
		                             }

		                             // 返回true以继续迭代
		                             return true;
	                             });
	if (ValidSaveSlotsRing.Num() > 1)
	{
		CurrentSaveNode = &ValidSaveSlotsRing.GetTail()->GetValue();
	}
}


void UGameSaveManager::InitializeNewSaveGame()
{
}

bool UGameSaveManager::PerformSaveGameToFile(const FSaveSlotInfo& SaveSlotName)
{
	UE_LOG(LogChamingCraftSave, Display, TEXT("[📦] Saving Save Slot: %s"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.PlayerData, SaveSlotName.SaveSlotName + "/" + FString("PlayerData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[📥] Save 1 files %s to Save Slot: %s"), *FString("PlayerData.sav"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.RealmData, SaveSlotName.SaveSlotName + "/" + FString("RealmData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[📥] Save 1 files %s to Save Slot: %s"), *FString("RealmData.sav"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.ProgressData,
	                                 SaveSlotName.SaveSlotName + "/" + FString("ProgressData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[📥] Save 1 files %s to Save Slot: %s"), *FString("ProgressData.sav"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.LevelData,
	                                 SaveSlotName.SaveSlotName + "/" + FString("LevelData"),
	                                 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[📥] Save 1 files %s to Save Slot: %s"), *FString("LevelData.sav"),
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

	if (ValidSaveSlotsRing.Num() > 1)
	{
		for (auto& SaveSlotName : ValidSaveSlotsRing)
		{
			if (SaveSlotName.IsIndicateBound)
			{
				continue;
			}
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

FSaveSlotInfo& UGameSaveManager::GetCurrentSaveSlot()
{
	return *CurrentSaveNode;
}

bool UGameSaveManager::SetCurrentSlot()
{
	if (ValidSaveSlotsRing.Num() > 1)
	{
		CurrentSaveNode = &ValidSaveSlotsRing.GetTail()->GetValue();
		return true;
	}
	else
	{
		CurrentSaveNode = &ValidSaveSlotsRing.GetHead()->GetValue();
		return false;
	}
}

bool UGameSaveManager::SetPreviewSlotAsCurrentSlot()
{
	if (ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetPrevNode())
	{
		CurrentSaveNode = &ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetPrevNode()->GetValue();
		return true;
	}
	else
	{
		if (ValidSaveSlotsRing.GetTail())
		{
			CurrentSaveNode = &ValidSaveSlotsRing.GetTail()->GetValue();
			return false;
		}
		else
		{
			return false;
		}
	}
}

FSaveSlotInfo& UGameSaveManager::GetPreviewSlot()
{
	if (ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetPrevNode())
	{
		return ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetPrevNode()->GetValue();
	}
	else
	{
		return ValidSaveSlotsRing.GetTail()->GetValue();
	}
}

bool UGameSaveManager::SetNextSlotAsCurrentSlot()
{
	if (ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetNextNode())
	{
		CurrentSaveNode = &ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetNextNode()->GetValue();
		return true;
	}
	else
	{
		if (ValidSaveSlotsRing.GetHead())
		{
			CurrentSaveNode = &ValidSaveSlotsRing.GetHead()->GetValue();
			return false;
		}
		else
		{
			return false;
		}
	}
}

FSaveSlotInfo& UGameSaveManager::GetNextSlot()
{
	if (ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetNextNode())
	{
		return ValidSaveSlotsRing.FindNode(*CurrentSaveNode)->GetNextNode()->GetValue();
	}
	else
	{
		return ValidSaveSlotsRing.GetHead()->GetValue();
	}
}

int32 UGameSaveManager::GetValidSaveSlotsRingNumber()
{
	return ValidSaveSlotsRing.Num();
}

bool UGameSaveManager::DeleteCurrentSaveSlot()
{
	UE_LOG(LogChamingCraftSave, Display, TEXT("[🛑] Deleting Save Slot: %s"),
	       *CurrentSaveNode->SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*CurrentSaveNode->SaveSlotName + FString("/PlayerData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"), *FString("PlayerData.sav"),
	       *CurrentSaveNode->SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*CurrentSaveNode->SaveSlotName + FString("/LevelData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"), *FString("LevelData.sav"),
	       *CurrentSaveNode->SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*CurrentSaveNode->SaveSlotName + FString("/ProgressData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"),
	       *FString("ProgressData.sav"),
	       *CurrentSaveNode->SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*CurrentSaveNode->SaveSlotName + FString("/RealmData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"),
	       *FString("RealmData.sav"),
	       *CurrentSaveNode->SaveSlotName);

	// 获取SaveGames目录的路径
	FString SaveGamesDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames");

	// 构建目标文件夹的完整路径
	FString TargetFolder = SaveGamesDirectory / FString(*CurrentSaveNode->SaveSlotName);

	// 获取文件管理器的实例
	IFileManager& FileManager = IFileManager::Get();

	// 删除目标目录，第二个参数为true表示递归删除
	bool bSuccess = FileManager.DeleteDirectory(*TargetFolder, false, true);

	if (bSuccess)
	{
		UE_LOG(LogChamingCraftSave, Display, TEXT("		[✔️] Complete Delete Save Slot Save Slot: %s"),
		       *CurrentSaveNode->SaveSlotName);
	}
	else
	{
		UE_LOG(LogChamingCraftSave, Display, TEXT("		[❌] Fail to Delete Save Slot Save Slot: %s"),
		       *CurrentSaveNode->SaveSlotName);
	}

	auto NextSlot = GetNextSlot();
	ValidSaveSlotsRing.RemoveNode(*CurrentSaveNode);
	CurrentSaveNode = &NextSlot;

	UpdateSaveSlots();
	PerformLoadGameFromFile();
	return true;
}
