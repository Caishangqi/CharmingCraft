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

public:
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
	TObjectPtr<UPlayerData> PlayerData;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URealmData> RealmData;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UProgressData> ProgressData;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ULevelData> LevelData;
};
