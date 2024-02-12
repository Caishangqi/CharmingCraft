#pragma once
#include "CoreMinimal.h"
#include "FPlayerLocation.generated.h"

USTRUCT(BlueprintType)
struct FPlayerLocation
{
	GENERATED_BODY()

public:
	FPlayerLocation(): PlayerLocation(0, 0, 0), LevelName("WorldSpawn")
	{
	}

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PlayerInformation")
	FVector PlayerLocation;

	// 在PlayerData.h中添加
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "LevelData")
	FString LevelName;
};
