#include "Biome.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h" // Optional: For debugging raycasts
#include "Components/BoxComponent.h"


ABiome::ABiome()
{
	PrimaryActorTick.bCanEverTick = true;
	BiomeBound = CreateDefaultSubobject<UBoxComponent>("Biome Bound");
	BiomeBound->SetupAttachment(RootComponent);
}

void ABiome::BeginPlay()
{
	Super::BeginPlay();

	// 遍历注册的BiomeData，生成资源实体
	for (const FBiomeData& BiomeData : RegisterBiomeData)
	{
		// 确定生成数量
		int32 NumToSpawn = FMath::RandRange(BiomeData.MinPerBiome, BiomeData.MaxPerBiome);

		for (int32 i = 0; i < NumToSpawn; ++i)
		{
			FVector SpawnLocation;
			if (GetRandomPointInVolume(SpawnLocation))
			{
				// 尝试在计算出的位置生成资源实体
				AResourceEntityActor* SpawnedActor = GetWorld()->SpawnActor<AResourceEntityActor>(
					BiomeData.ResourceEntityActorClass, SpawnLocation, FRotator::ZeroRotator);
				if (SpawnedActor)
				{
					ResourceEntityActorPool.Add(SpawnedActor);
				}
			}
		}
	}
}

bool ABiome::GetRandomPointInVolume(FVector& OutLocation)
{
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(false, Origin, BoxExtent);

	FVector RandPoint = Origin + FMath::RandPointInBox(FBox(-BoxExtent, BoxExtent));

	// 射线投射以检查地面
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // 忽略自身
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, RandPoint, RandPoint - FVector(0, 0, 10000),
	                                                 ECC_WorldStatic, CollisionParams);

	if (bHit)
	{
		// 检查到地面，返回地面上方的位置
		OutLocation = HitResult.Location;
		return true;
	}

	// 没有检查到地面，返回失败
	return false;
}

void ABiome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
