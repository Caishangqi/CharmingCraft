#pragma once
#include "CoreMinimal.h"
#include "FPlayerLocation.generated.h"

USTRUCT(BlueprintType)
struct FPlayerLocation
{
	GENERATED_BODY()

public:
	FPlayerLocation(): PlayerRotation(0, 0, 0), PlayerLocation(0, 0, 0), LevelName("WorldSpawn"), bIsSpawnPoint(true),
	                   Level(nullptr)
	{
	}

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerInformation")
	FRotator PlayerRotation;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerInformation")
	FVector PlayerLocation;
	// 在PlayerData.h中添加
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "LevelData")
	FString LevelName;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "SpawnData")
	bool bIsSpawnPoint;

	// Runtime
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Level Runtime Data")
	TSoftObjectPtr<UWorld> Level;
};
