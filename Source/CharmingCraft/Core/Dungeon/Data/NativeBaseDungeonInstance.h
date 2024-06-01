// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "UObject/Object.h"
#include "NativeBaseDungeonInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, notplaceable)
class CHARMINGCRAFT_API ANativeBaseDungeonInstance : public AInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHasHub = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxChildDungeonsPerInstance = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bLoadDungeonsWorldsByNeed = true; // Whether load the world to world manager when needed
	
	/*
	 *	In the Array,put hub map to 0 index if possible, if a dungeon do not
	 *	have a hub, always put the first map to index 1.
	 */
	

	// Predefine the map for each child dungeons
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> ChildDungeonsWorlds;
	// 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCharmingCraftWorld> ChildDungeonsWorldsInstance;
	// Define player in which child dungeons, for example, <PlayerA, 3> means
	// PlayerA is in 3rd ChildDungeon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<ACharacter *, int> DungeonInstancePlayerData;
};
