// Fill out your copyright notice in the Description page of Project Settings.


#include "LandChunk.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Resource/Lib/ResourceGenerateLibrary.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"


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
	TopLayer->SetRelativeLocation(FVector(0, -1000, 0));
	TopLayer->SetRelativeScale3D(FVector(10, 10, 3));

	MiddleLayer->SetRelativeLocation(FVector(0, -1000, -400));
	MiddleLayer->SetRelativeScale3D(FVector(10, 10, 4));

	BottomLayer->SetRelativeLocation(FVector(0, -1000, -700));
	BottomLayer->SetRelativeScale3D(FVector(10, 10, 3));

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
				DrawDebugPoint(this->GetWorld(), FVector(Point_X, Point_Y, Point_Z), 10, FColor::Yellow, false, 10.0f);
			}
		}
	}
}


void ALandChunk::OnUnloadWorldChunkEvent(UObject* InstigatorObject, UWorld* TargetWorld, ALandChunk* TargetChunk)
{
	// Execute OnUnloadChunk
	if (TargetChunk == this)
	{
		// Set Chunk state
		SetActorTickEnabled(false);
		ChunkState = EChunkState::PENDING_UNLOADED;
		GetWorldTimerManager().ClearAllTimersForObject(TargetWorld);
		for (auto& PerBiomeData : BiomeData)
		{
			/*UE_LOG(LogChamingCraftWorld, Error,
			       TEXT("[🌍]  Timer Status Before clear: %d\n"
				       "		Timer Owner: %s\n"
				       "		Timer Valid: %d"),
			       GetWorldTimerManager().IsTimerActive(PerBiomeData.ResourceInternalTimer),
			       *PerBiomeData.ResourceInternalTimer.ToString(), PerBiomeData.ResourceInternalTimer.IsValid());*/
			GetWorldTimerManager().ClearTimer(PerBiomeData.ResourceInternalTimer);
			/*UE_LOG(LogChamingCraftWorld, Error,
			       TEXT("[🌍]  Timer Status: %d\n"
				       "		Timer Owner: %s\n"
				       "		Timer Valid: %d"),
			       GetWorldTimerManager().IsTimerActive(PerBiomeData.ResourceInternalTimer),
			       *PerBiomeData.ResourceInternalTimer.ToString(), PerBiomeData.ResourceInternalTimer.IsValid());*/
		}
		ChunkState = EChunkState::UNLOADED;
		// Then We start serialize data (resource pool)

		// Destroy
	}
}

void ALandChunk::OnResourceEntityBreakEvent(AActor* Breaker, AResourceEntityActor* TargetResourceEntity)
{
	UE_LOG(LogChamingCraftResource, Display,
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
	for (auto& PerBiomeData : BiomeData)
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
	float SuccessRate = GetOnGenerateSuccessRate(BiomeDataContext);
	float RandomChance = FMath::FRand();

	if (RandomChance > SuccessRate)
	{
		return; // Early exit if the random chance exceeds success rate
	}

	int32 RandomIndex = FMath::RandRange(0, ChunkPoints.Num() - 1);
	FVector SpawnLocation = ChunkPoints[RandomIndex] + FVector(0, 0, 500);
	// Generate Random Rotation
	float RandomYaw = UResourceGenerateLibrary::GetRandomYawRight();

	FTransform SpawnTransform(FRotator(0, RandomYaw, 0), SpawnLocation);
	/*
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  The resource is spawn in world: %s"), *GetWorld()->GetName());
	       */

	TObjectPtr<AResourceEntityActor> ResourceEntityActor;
	/* 请务必确保Owner是当前Actor,这样他就会和关卡一起卸载加载 */
	ResourceEntityActor = Cast<AResourceEntityActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(
			this, BiomeDataContext.ResourceEntityActorClass,
			SpawnTransform, ESpawnActorCollisionHandlingMethod::Undefined, this));
	if (!ResourceEntityActor)
	{
		return; // Early exit if actor casting fails
	}

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(ResourceEntityActor);

	TArray<float> Z_Plane;
	bool bValidSpawn = true; // Assume valid spawn until proven otherwise

	for (FVector CornerVector : UResourceGenerateLibrary::GetBoxCornerVector(ResourceEntityActor->HitBox))
	{
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CornerVector + FVector(0, 0, 1000),
		                                                 CornerVector - FVector(0, 0, 500),
		                                                 ECC_WorldStatic, CollisionParams);
		DrawDebugLine(this->GetWorld(), CornerVector, CornerVector - FVector(0, 0, 500), FColor::Purple, false,
		              10.0f);

		if (bHit)
		{
			Z_Plane.Add(HitResult.Location.Z);
		}
		else
		{
			bValidSpawn = false;
			break; // Exit loop early if any corner does not hit
		}
	}

	if (bValidSpawn && UResourceGenerateLibrary::AreAllElementsTheSame(Z_Plane) && Z_Plane.Num() == 4)
	{
		FHitResult SecondTraceHitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(SecondTraceHitResult, SpawnLocation,
		                                                 ChunkPoints[RandomIndex],
		                                                 ECC_WorldStatic, CollisionParams);
		DrawDebugLine(this->GetWorld(), ChunkPoints[RandomIndex] + FVector(0, 0, 500), ChunkPoints[RandomIndex],
		              FColor::Yellow, false, 10.0f);

		if (bHit && (SecondTraceHitResult.GetActor()->IsA(AStaticMeshActor::StaticClass()) ||
			(SecondTraceHitResult.GetActor() == this && SecondTraceHitResult.Component == TopLayer)))
		{
			FVector FinalLocation(SecondTraceHitResult.Location);
			FTransform FinalTransform(FRotator(0, RandomYaw, 0), FinalLocation);
			UGameplayStatics::FinishSpawningActor(ResourceEntityActor, FinalTransform);
			ResourceEntityActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			ResourceEntityActorPool.Add(ResourceEntityActor);
		}
		else
		{
			bValidSpawn = false;
		}
	}
	else
	{
		bValidSpawn = false;
	}

	if (!bValidSpawn)
	{
		if (ResourceEntityActor)
		{
			ResourceEntityActor->Destroy();
		}
	}
}


// Called when the game starts or when spawned
void ALandChunk::BeginPlay()
{
	Super::BeginPlay();
	if (ChunkState == EChunkState::LOADED)
	{
		StartBiomeDataTimer();
	}
	GameEventHandler = Cast<UCharmingCraftInstance>(GetGameInstance())->GamePlayLogicManager;
	GameEventHandler->OnResourceEntityBreak.AddDynamic(this, &ALandChunk::OnResourceEntityBreakEvent);
	GameEventHandler->OnUnloadWorldChunk.AddDynamic(this, &ALandChunk::OnUnloadWorldChunkEvent);
}

void ALandChunk::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto& PerBiomeData : BiomeData)
	{
		GetWorld()->GetTimerManager().ClearTimer(PerBiomeData.ResourceInternalTimer);
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ALandChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
