#include "Biome.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h" // Optional: For debugging raycasts
#include "CharmingCraft/Core/Builds/Lib/BuildModuleLib.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
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
	GameEventHandler = Cast<UCharmingCraftInstance>(GetGameInstance())->GamePlayLogicManager;
	GameEventHandler->OnResourceEntityBreak.AddDynamic(this, &ABiome::OnResourceEntityBreakEvent);

	// Init Biome with some preload resource actor
	InitBiomeActor();

	// Register Timer, keep generate resource
	StartBiomeDataTimer();
}

bool ABiome::GetRandomPointInVolume(FVector& OutLocation)
{
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(false, Origin, BoxExtent);

	FVector RandPoint = UBuildModuleLib::SnapToGrid(Origin + FMath::RandPointInBox(FBox(-BoxExtent, BoxExtent)), 100);;


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

void ABiome::OnResourceEntityBreakEvent(AActor* Breaker, AResourceEntityActor* TargetResourceEntity)
{
	UE_LOG(LogChamingCraftResource, Display,
	       TEXT("[🪨️]  Biome Internal resource actor update\n"
		       "		 [B] Biome =		%s\n"
		       "		 [R] Resource =		%s\n"
		       "		 [I] Instigator =	%s"), *BiomeRegisterName.ToString(),
	       *TargetResourceEntity->ResourceName.ToString(), *Breaker->GetName());
	ResourceEntityActorPool.Remove(TargetResourceEntity);
}

float ABiome::GetOnGenerateSuccessRate(FBiomeData BiomeData)
{
	int32 BiomeIncludeResource = 0;
	for (auto ResourceEntity : ResourceEntityActorPool)
	{
		if (ResourceEntity.GetClass() == BiomeData.ResourceEntityActorClass.Get())
		{
			BiomeIncludeResource++;
		}
	}
	return 1 - (BiomeIncludeResource / BiomeData.MaxPerBiome);
}

bool ABiome::StartBiomeDataTimer()
{
	for (auto &BiomeData : RegisterBiomeData)
	{

		GetWorld()->GetTimerManager().SetTimer(BiomeData.ResourceInternalTimer, [this, BiomeData]()
		                                       {
			                                       this->GenerateResource(BiomeData);
		                                       },
		                                       BiomeData.RegenerateTick, true);
	}
	return true;
}

void ABiome::GenerateResource(FBiomeData BiomeData)
{
	// 获取生成成功的概率
	float SuccessRate = GetOnGenerateSuccessRate(BiomeData);

	// 生成一个0到1之间的随机数
	float RandomChance = FMath::FRand();

	// 如果随机数小于等于生成几率，则生成Actor
	if (RandomChance <= SuccessRate)
	{
		if (!this)
		{
			return;
		}
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

void ABiome::InitBiomeActor()
{
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


void ABiome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
