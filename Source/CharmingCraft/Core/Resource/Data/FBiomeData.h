#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Resource/Gather/ResourceEntityActor.h"
#include "FBiomeData.generated.h"

USTRUCT(BlueprintType)
struct FBiomeData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Biome Data Name")
	FName BiomeDataName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Entity Actor Class")
	TSubclassOf<AResourceEntityActor> ResourceEntityActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Data")
	int32 MaxPerBiome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Data")
	int32 MinPerBiome;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Data")
	int32 MinRegenerateTick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Resource Data")
	int32 MaxRegenerateTick;
};
