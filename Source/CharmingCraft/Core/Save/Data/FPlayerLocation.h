#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/World/NativeCraftWorld.h"
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
	UE_DEPRECATED(5.3, "The WorldManager has been refactory, please use new API")
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Level Runtime Data")
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Level Runtime Data")
	TObjectPtr<UNativeCraftWorld> GameWorld;
};
