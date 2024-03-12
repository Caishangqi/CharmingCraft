// Fill out your copyright notice in the Description page of Project Settings.


#include "LandChunk.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Engine/StaticMeshActor.h"


// Sets default values
ALandChunk::ALandChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SceneComponent->SetRelativeLocation(FVector(0, 0, 0));
	RootComponent = SceneComponent;

	BottomLayer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom Layer"));
	MiddleLayer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle Layer"));
	TopLayer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top Layer"));
	// (X=0.000000,Y=-1000.000000,Z=0.000000)
	TopLayer->SetRelativeLocation(FVector(0,-1000,0));
	TopLayer->SetRelativeScale3D(FVector(10,10,3));
	
	MiddleLayer->SetRelativeLocation(FVector(0,-1000,-400));
	MiddleLayer->SetRelativeScale3D(FVector(10,10,4));

	BottomLayer->SetRelativeLocation(FVector(0,-1000,-700));
	BottomLayer->SetRelativeScale3D(FVector(10,10,3));
	
	BottomLayer->SetupAttachment(RootComponent);
	MiddleLayer->SetupAttachment(RootComponent);
	TopLayer->SetupAttachment(RootComponent);

	
	
}

void ALandChunk::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);
	if (bFinished)
	{
		FVector Min, Max;
		TopLayer->GetLocalBounds(Min, Max);
		const FVector Scale = TopLayer->GetRelativeScale3D();
		ChunkPoints.Empty();
		const FVector Size = Max * Scale - Min;
		NumberCell_X = UE4::SSE::CeilToInt32(Size.X / GridSize);
		NumberCell_Y = UE4::SSE::CeilToInt32(Size.Y / GridSize);
		ChunkPoints.Reserve(NumberCell_X * NumberCell_Y); // Reserve capacity upfront
		GridCell_X = NumberCell_X - 1;
		GridCell_Y = NumberCell_Y - 1;

		FVector ChunkLocation = GetActorLocation();
		int32 Point_Z = ChunkLocation.Z;
		int32 BasePoint_X = ChunkLocation.X + 50; // Calculate once
		int32 BasePoint_Y = ChunkLocation.Y - 50; // Calculate once

		for (int index_X = 0; index_X <= GridCell_X; ++index_X)
		{
			int32 Point_X = index_X * GridSize + BasePoint_X;
			for (int index_Y = 0; index_Y <= GridCell_Y; ++index_Y)
			{
				const int32 Point_Y = (index_Y * GridSize * -1) + BasePoint_Y;
				ChunkPoints.Add(FVector(Point_X, Point_Y, Point_Z));
				DrawDebugPoint(this->GetWorld(),FVector(Point_X,Point_Y,Point_Z),10,FColor::Yellow,false,10.0f);
			}
		}
	}
}


void ALandChunk::OnResourceEntityBreakEvent(APawn* Breaker, AResourceEntityActor* TargetResourceEntity)
{
	UE_LOG(LogChamingCraftCraftResource, Display,
	   TEXT("[🪨️]  Chunk Internal resource actor update\n"
		   "		 [C] Chunk =		%s\n"
		   "		 [R] Resource =		%s\n"
		   "		 [I] Instigator =	%s"), *this->GetName(),
	   *TargetResourceEntity->ResourceName.ToString(), *Breaker->GetName());
	ResourceEntityActorPool.Remove(TargetResourceEntity);
}

float ALandChunk::GetOnGenerateSuccessRate(FBiomeData BiomeDataContext)
{
	int32 BiomeIncludeResource = 0;
	for (auto ResourceEntity : ResourceEntityActorPool)
	{
		if (ResourceEntity.GetClass() == BiomeDataContext.ResourceEntityActorClass.Get())
		{
			BiomeIncludeResource++;
		}
	}
	return 1 - (BiomeIncludeResource / BiomeDataContext.MaxPerBiome);
}

bool ALandChunk::StartBiomeDataTimer()
{
	for (auto PerBiomeData : BiomeData)
	{
		GetWorld()->GetTimerManager().SetTimer(PerBiomeData.ResourceInternalTimer, [this, PerBiomeData]()
											   {
												   this->GenerateResource(PerBiomeData);
											   },
											   PerBiomeData.RegenerateTick, true);
	}
	return true;
}

void ALandChunk::GenerateResource(FBiomeData BiomeDataContext)
{
	// 获取生成成功的概率
	float SuccessRate = GetOnGenerateSuccessRate(BiomeDataContext);

	// 生成一个0到1之间的随机数
	float RandomChance = FMath::FRand();

	// 如果随机数小于等于生成几率，则生成Actor
	if (RandomChance <= SuccessRate)
	{
		
		int32 RandomIndex = FMath::RandRange(0, ChunkPoints.Num() - 1);

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		//CollisionParams.AddIgnoredActor(this); // 忽略自身
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ChunkPoints[RandomIndex]+ FVector(0, 0, 5000), ChunkPoints[RandomIndex] ,
														 ECC_WorldStatic, CollisionParams);
		
		if (bHit)
		{
			if (HitResult.GetActor()->IsA(AStaticMeshActor::StaticClass()))
			{
				// 判断是否能在指定材质上生成, 等待实现
				AResourceEntityActor* SpawnedActor = GetWorld()->SpawnActor<AResourceEntityActor>(
				BiomeDataContext.ResourceEntityActorClass, HitResult.Location, FRotator::ZeroRotator);
				if (SpawnedActor)
				{
					ResourceEntityActorPool.Add(SpawnedActor);
				}
			}
			if (HitResult.GetActor() == this && HitResult.Component == TopLayer)
			{
				AResourceEntityActor* SpawnedActor = GetWorld()->SpawnActor<AResourceEntityActor>(
				BiomeDataContext.ResourceEntityActorClass, HitResult.Location, FRotator::ZeroRotator);
				if (SpawnedActor)
				{
					ResourceEntityActorPool.Add(SpawnedActor);
				}
			}
			// 尝试在计算出的位置生成资源实体
		}
	}
}


// Called when the game starts or when spawned
void ALandChunk::BeginPlay()
{
	Super::BeginPlay();
	GameEventHandler = Cast<UCharmingCraftInstance>(GetGameInstance())->GamePlayLogicManager;
	GameEventHandler->OnResourceEntityBreak.AddDynamic(this, &ALandChunk::OnResourceEntityBreakEvent);

	StartBiomeDataTimer();
}

// Called every frame
void ALandChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

