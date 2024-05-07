#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Resource/Gather/ResourceEntityActor.h"
#include "CharmingCraft/Core/Entity/Creature/NativeCreature.h"
#include "FBiomeData.generated.h"

USTRUCT(BlueprintType)
struct FBiomeData
{
	GENERATED_BODY()

public:
	FBiomeData(): CreatureEntityActorClass(nullptr), MaxPerBiome(0), MinPerBiome(0),
	              RegenerateTick(0), SuccessRate(0)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Biome Data Name")
	FName BiomeDataName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Entity Actor Class")
	TSubclassOf<AResourceEntityActor> ResourceEntityActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Creature Entity Actor Class")
	TSubclassOf<ANativeCreature> CreatureEntityActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Data")
	int32 MaxPerBiome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Data")
	int32 MinPerBiome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Data")
	int32 RegenerateTick;


	/*
	 *	间隔多少秒进行一次生成尝试
	 *	如果 ResourceInternalTimer = 4, 成功率公式为  1 - (current / max)
	 *	则 Biome 每隔4秒尝试一次生成,单词生成有 % 1 - (current / max) 成功生成资源
	 */
	FTimerHandle ResourceInternalTimer; // 4
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Internal Timer")
	float SuccessRate; // 单词尝试成功几率 1 - (current / max)
};
