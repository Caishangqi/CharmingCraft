#pragma once
#include "CoreMinimal.h"
#include "LevelData.h"
#include "PlayerData.h"
#include "RealmData.h"
#include "ProgressData.h"
#include "FSaveSlotInfo.generated.h"

USTRUCT(BlueprintType)
struct FSaveSlotInfo
{
	GENERATED_BODY()
	FSaveSlotInfo(): SaveSlotID(0), SaveSlotPath(""), SaveSlotRelativePath(""), SaveSlotName(""), bPrepareDelete(false),
	                 IsIndicateBound(false), PlayerData(nullptr), RealmData(nullptr),
	                 ProgressData(nullptr), LevelData(nullptr)
	{
	}

public:
	// 存档的唯一标识符
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "SaveData")
	FGuid UniqueID;

	UPROPERTY(BlueprintReadWrite)
	int32 SaveSlotID;
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotPath;
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotRelativePath; // Player View
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotName;
	UPROPERTY(BlueprintReadWrite)
	bool bPrepareDelete;
	UPROPERTY(BlueprintReadWrite)
	bool IsIndicateBound;
	UPROPERTY(BlueprintReadWrite)
	UPlayerData* PlayerData;
	UPROPERTY(BlueprintReadWrite)
	URealmData* RealmData;
	UPROPERTY(BlueprintReadWrite)
	UProgressData* ProgressData;
	UPROPERTY(BlueprintReadWrite)
	ULevelData* LevelData;

	friend bool operator==(const FSaveSlotInfo& Lhs, const FSaveSlotInfo& RHS)
	{
		return Lhs.SaveSlotID == RHS.SaveSlotID
			&& Lhs.SaveSlotPath == RHS.SaveSlotPath
			&& Lhs.SaveSlotRelativePath == RHS.SaveSlotRelativePath
			&& Lhs.SaveSlotName == RHS.SaveSlotName
			&& Lhs.bPrepareDelete == RHS.bPrepareDelete
			&& Lhs.IsIndicateBound == RHS.IsIndicateBound
			&& Lhs.PlayerData == RHS.PlayerData
			&& Lhs.RealmData == RHS.RealmData
			&& Lhs.ProgressData == RHS.ProgressData
			&& Lhs.LevelData == RHS.LevelData;
	}

	friend bool operator!=(const FSaveSlotInfo& Lhs, const FSaveSlotInfo& RHS)
	{
		return !(Lhs == RHS);
	}
};
