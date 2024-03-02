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
	//FSaveSlotInfo BoundarySlot;
	CurrentSaveNode = FSaveSlotInfo();
	CurrentSaveNode.IsIndicateBound = true;
	ValidSaveSlotsRing.AddHead(CurrentSaveNode);

	/* End Initialize Boundary Slot */
	UpdateSaveSlots();
	PerformLoadGamesFromFile();
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
		CurrentSaveNode = ValidSaveSlotsRing.GetTail()->GetValue();
	}
}


bool UGameSaveManager::PerformSaveGameToFile(const FSaveSlotInfo& SaveSlotName)
{
	UE_LOG(LogChamingCraftSave, Display, TEXT("[💾] Saving Save Slot to Disk: %s"),
	       *SaveSlotName.SaveSlotName);
	UGameplayStatics::SaveGameToSlot(SaveSlotName.PlayerData,
	                                 SaveSlotName.SaveSlotName + "/" + FString("PlayerData"),
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


	return true;
}

bool UGameSaveManager::PerformSaveGamesToFile()
{
	for (auto Element : ValidSaveSlotsRing)
	{
		if (!Element.IsIndicateBound)
		{
			PerformSaveGameToFile(Element);
		}
	}
	return true;
}

void UGameSaveManager::PerformLoadGamesFromFile()
{
	if (ValidSaveSlotsRing.Num() > 1)
	{
		for (auto& SaveSlotName : ValidSaveSlotsRing)
		{
			if (SaveSlotName.IsIndicateBound)
			{
				continue;
			}
			SaveSlotName.PlayerData = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(
				SaveSlotName.SaveSlotName + "/" + FString("PlayerData"),
				0));
			SaveSlotName.PlayerData->UniqueID = SaveSlotName.UniqueID; //
			SaveSlotName.LevelData = Cast<ULevelData>(UGameplayStatics::LoadGameFromSlot(
				SaveSlotName.SaveSlotName + "/" + FString("LevelData"),
				0));
			SaveSlotName.LevelData->UniqueID = SaveSlotName.UniqueID; //
			SaveSlotName.ProgressData = Cast<UProgressData>(UGameplayStatics::LoadGameFromSlot(
				SaveSlotName.SaveSlotName + "/" + FString("ProgressData"),
				0));
			SaveSlotName.ProgressData->UniqueID = SaveSlotName.UniqueID; //
			SaveSlotName.RealmData = Cast<URealmData>(UGameplayStatics::LoadGameFromSlot(
				SaveSlotName.SaveSlotName + "/" + FString("RealmData"),
				0));
			SaveSlotName.RealmData->UniqueID = SaveSlotName.UniqueID; //

			if (SaveSlotName.PlayerData->PlayerInfo.IsSelected)
			{
				CurrentSaveNode = SaveSlotName;
			}
		}
	}
}

bool UGameSaveManager::SaveGameToGameSlot()
{
	if (!GetCurrentSaveSlot().IsIndicateBound)
	{
		if (GetCurrentSaveSlot().PlayerData != nullptr)
		{
			GetCurrentSaveSlot().PlayerData->PerformSavePlayerDataToSlot(Cast<UCharmingCraftInstance>(GetOuter()));
		}
		else
		{
			// Log an error message or handle the error
		}
	}

	PerformSaveGameToFile(GetCurrentSaveSlot());
	return false;
}

bool UGameSaveManager::CreateNewSlotAndSave(FSaveSlotInfo SaveSlotName)
{
	if (PerformSaveGameToFile(SaveSlotName))
	{
		ValidSaveSlotsRing.AddTail(SaveSlotName);
		CurrentSaveNode = SaveSlotName;
		return true;
	}
	return false;
}

void UGameSaveManager::PerformLoadGameFromFile(FSaveSlotInfo& SaveSlotName)
{
	if (!SaveSlotName.IsIndicateBound)
	{
		UE_LOG(LogChamingCraftSave, Display, TEXT("[🔍] Load Save Slot: %s"), *SaveSlotName.SaveSlotName);
		SaveSlotName.PlayerData = Cast<UPlayerData>(UGameplayStatics::LoadGameFromSlot(
			SaveSlotName.SaveSlotName + "/" + FString("PlayerData"),
			0)); // PlayerData
		UE_LOG(LogChamingCraftSave, Display, TEXT("	[📤] Load 1 SaveGame %s From Save Slot: %s"),
		       *FString("PlayerData.sav"),
		       *SaveSlotName.SaveSlotName);
		SaveSlotName.PlayerData->UniqueID = SaveSlotName.UniqueID; //
		SaveSlotName.LevelData = Cast<ULevelData>(UGameplayStatics::LoadGameFromSlot(
			SaveSlotName.SaveSlotName + "/" + FString("LevelData"),
			0)); // LevelData
		UE_LOG(LogChamingCraftSave, Display, TEXT("	[📤] Load 1 SaveGame %s From Save Slot: %s"),
		       *FString("LevelData.sav"),
		       *SaveSlotName.SaveSlotName);
		SaveSlotName.LevelData->UniqueID = SaveSlotName.UniqueID; //
		SaveSlotName.ProgressData = Cast<UProgressData>(UGameplayStatics::LoadGameFromSlot(
			SaveSlotName.SaveSlotName + "/" + FString("ProgressData"),
			0)); // ProgressData
		UE_LOG(LogChamingCraftSave, Display, TEXT("	[📤] Load 1 SaveGame %s From Save Slot: %s"),
		       *FString("ProgressData.sav"),
		       *SaveSlotName.SaveSlotName);
		SaveSlotName.ProgressData->UniqueID = SaveSlotName.UniqueID; //
		SaveSlotName.RealmData = Cast<URealmData>(UGameplayStatics::LoadGameFromSlot(
			SaveSlotName.SaveSlotName + "/" + FString("RealmData"),
			0)); // RealmData
		UE_LOG(LogChamingCraftSave, Display, TEXT("	[📤] Load 1 SaveGame %s From Save Slot: %s"),
		       *FString("RealmData.sav"),
		       *SaveSlotName.SaveSlotName);
		SaveSlotName.RealmData->UniqueID = SaveSlotName.UniqueID; //
	}
}

FSaveSlotInfo& UGameSaveManager::GetCurrentSaveSlot()
{
	return CurrentSaveNode;
}

bool UGameSaveManager::SetCurrentSlot()
{
	if (ValidSaveSlotsRing.Num() > 1)
	{
		CurrentSaveNode = ValidSaveSlotsRing.GetTail()->GetValue();
		return true;
	}
	CurrentSaveNode = ValidSaveSlotsRing.GetHead()->GetValue();
	return false;
}

bool UGameSaveManager::SetPreviewSlotAsCurrentSlot()
{
	if (ValidSaveSlotsRing.FindNode(CurrentSaveNode) && ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetPrevNode())
	{
		CurrentSaveNode = ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetPrevNode()->GetValue();
		return true;
	}
	if (ValidSaveSlotsRing.GetTail())
	{
		CurrentSaveNode = ValidSaveSlotsRing.GetTail()->GetValue();
		return false;
	}
	return false;
}

FSaveSlotInfo& UGameSaveManager::GetPreviewSlot()
{
	if (ValidSaveSlotsRing.Contains(CurrentSaveNode) && ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetPrevNode())
	{
		return ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetPrevNode()->GetValue();
	}

	// if (ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetPrevNode())
	// {
	// 	return ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetPrevNode()->GetValue();
	// }
	return ValidSaveSlotsRing.GetTail()->GetValue();
}

bool UGameSaveManager::SetNextSlotAsCurrentSlot()
{
	if (ValidSaveSlotsRing.FindNode(CurrentSaveNode) && ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetNextNode())
	{
		CurrentSaveNode = ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetNextNode()->GetValue();
		return true;
	}
	if (ValidSaveSlotsRing.GetHead())
	{
		CurrentSaveNode = ValidSaveSlotsRing.GetHead()->GetValue();
		return false;
	}
	return false;
}

FSaveSlotInfo& UGameSaveManager::GetNextSlot()
{
	if (ValidSaveSlotsRing.Contains(CurrentSaveNode) && ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetNextNode())
	{
		return ValidSaveSlotsRing.FindNode(CurrentSaveNode)->GetNextNode()->GetValue();
	}
	return ValidSaveSlotsRing.GetHead()->GetValue();
}

int32 UGameSaveManager::GetValidSaveSlotsRingNumber()
{
	return ValidSaveSlotsRing.Num();
}

bool UGameSaveManager::DeleteCurrentSaveSlot()
{
	FSaveSlotInfo PrepareDeleteNode = CurrentSaveNode;
	ValidSaveSlotsRing.RemoveNode(CurrentSaveNode);
	CurrentSaveNode = GetNextSlot();

	UE_LOG(LogChamingCraftSave, Display, TEXT("[🛑] Deleting Save Slot: %s"),
	       *PrepareDeleteNode.SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*PrepareDeleteNode.SaveSlotName + FString("/PlayerData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"),
	       *FString("PlayerData.sav"),
	       *PrepareDeleteNode.SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*PrepareDeleteNode.SaveSlotName + FString("/LevelData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"),
	       *FString("LevelData.sav"),
	       *PrepareDeleteNode.SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*PrepareDeleteNode.SaveSlotName + FString("/ProgressData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"),
	       *FString("ProgressData.sav"),
	       *PrepareDeleteNode.SaveSlotName);
	UGameplayStatics::DeleteGameInSlot(FString(*PrepareDeleteNode.SaveSlotName + FString("/RealmData")), 0);
	UE_LOG(LogChamingCraftSave, Display, TEXT("	[❌] Delete 1 files %s from Save Slot: %s"),
	       *FString("RealmData.sav"),
	       *PrepareDeleteNode.SaveSlotName);

	// 获取SaveGames目录的路径
	FString SaveGamesDirectory = FPaths::ProjectSavedDir() / TEXT("SaveGames");

	// 构建目标文件夹的完整路径
	FString TargetFolder = SaveGamesDirectory / FString(*PrepareDeleteNode.SaveSlotName);

	// 获取文件管理器的实例
	IFileManager& FileManager = IFileManager::Get();

	// 删除目标目录，第二个参数为true表示递归删除
	bool bSuccess = FileManager.DeleteDirectory(*TargetFolder, false, true);

	if (bSuccess)
	{
		UE_LOG(LogChamingCraftSave, Display, TEXT("		[✔️] Complete Delete Save Slot Save Slot: %s"),
		       *PrepareDeleteNode.SaveSlotName);
		PrepareDeleteNode.bPrepareDelete = true;
	}
	else
	{
		UE_LOG(LogChamingCraftSave, Display, TEXT("		[❌] Fail to Delete Save Slot Save Slot: %s"),
		       *PrepareDeleteNode.SaveSlotName);
	}


	UpdatePlayerMeshRenderActorInfo();
	//RefreshSaveSlotRing();
	return true;
}

void UGameSaveManager::SetSelectStateForSlot()
{
	for (FSaveSlotInfo& ElementSaveSlotInfo : ValidSaveSlotsRing)
	{
		if (!ElementSaveSlotInfo.IsIndicateBound)
		{
			ElementSaveSlotInfo.PlayerData->PlayerInfo.IsSelected = false;
		}
	}

	GetCurrentSaveSlot().PlayerData->PlayerInfo.IsSelected = true;
	PerformSaveGamesToFile();
}

bool UGameSaveManager::RefreshSaveSlotRing()
{
	for (const FSaveSlotInfo& ElementSaveSlotInfo : ValidSaveSlotsRing)
	{
		if (ElementSaveSlotInfo.bPrepareDelete)
		{
			if (ValidSaveSlotsRing.FindNode(ElementSaveSlotInfo)->GetNextNode() == nullptr)
			{
				CurrentSaveNode = ValidSaveSlotsRing.GetHead()->GetValue();
				ValidSaveSlotsRing.RemoveNode(ElementSaveSlotInfo);
			}
			else
			{
				CurrentSaveNode = ValidSaveSlotsRing.FindNode(ElementSaveSlotInfo)->GetNextNode()->GetValue();
				ValidSaveSlotsRing.RemoveNode(ElementSaveSlotInfo);
			}
			return true;
		}
	}
	return false;
}

void UGameSaveManager::UpdatePlayerMeshRenderActorInfo()
{
	CharacterDisplayMiddle->UpdatePreviewBaseSaveManager();
	CharacterDisplayLeft->UpdatePreviewBaseSaveManager();
	CharacterDisplayRight->UpdatePreviewBaseSaveManager();
}
