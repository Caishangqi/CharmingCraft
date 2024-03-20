// Fill out your copyright notice in the Description page of Project Settings.


#include "CropEntityActor.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"


// Sets default values
ACropEntityActor::ACropEntityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CropMesh = CreateDefaultSubobject<UStaticMeshComponent>("Crop Mesh");
	CropMesh->SetRelativeLocation(FVector(0, 0, 0));
	CropMesh->SetupAttachment(RootComponent);

	CurrentStage = 1;
	bDropSelf = false;
}

bool ACropEntityActor::OnBlockPlace_Implementation(AActor* InstigatorActor, AActor* BlockPlaced)
{
	StartGrowthTick();
	return Super::OnBlockPlace_Implementation(InstigatorActor, BlockPlaced);
}

bool ACropEntityActor::OnBlockDrop_Implementation(AActor* Block, UDropTableData* DropTableDataContext)
{
	return Super::OnBlockDrop_Implementation(Block, GetDropTableFromGrowthStage());
}

bool ACropEntityActor::OnBlockBreak_Implementation(AActor* InstigatorContext, AActor* BlockBreak)
{
	GameEventHandler->OnResourceEntityBreakEvent(InstigatorContext, this);

	return Execute_OnBlockDrop(this, InstigatorContext, nullptr);
	// Implement whether destroy the crops or modify stage
}

int32 ACropEntityActor::SetGrowthStage(int32 TargetStage)
{
	if (TargetStage <= CropData.CropStageMesh.Num() || TargetStage <= 0)
	{
		CurrentStage = TargetStage;
		CropMesh->SetStaticMesh(CropData.CropStageMesh.Find(TargetStage)->Get());
		return CurrentStage;
	}
	else
	{
		CurrentStage = 1;
		UE_LOG(LogChamingCraftResource, Error,
		       TEXT("[⛏️]  ACropEntityActor::SetGrowthStage: Invalid Growth Stage"));
		return CurrentStage;
	}
}

UDropTableData* ACropEntityActor::GetDropTableFromGrowthStage_Implementation()
{
	TSubclassOf<UDropTableData> DropTable = CropData.CropStageDrop.Find(CurrentStage)->Get();
	if (DropTable)
	{
		DropTableData = DropTable.Get();
	}

	return DropTable.GetDefaultObject();
}

void ACropEntityActor::StopGrowthTick_Implementation()
{
	GetWorld()->GetTimerManager().PauseTimer(CropGrowthTimer);
}

void ACropEntityActor::StartGrowthTick_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(CropGrowthTimer, this, &ACropEntityActor::OnGrowthTick, 1, true);
}

void ACropEntityActor::OnGrowthTick_Implementation()
{
	CurrentStageCount = CurrentStageCount + 1 * CropData.GrowthMultiplier;
	if (CurrentStageCount >= *CropData.PerStageCount.Find(CurrentStage))
	{
		if (CurrentStage == CropData.PerStageCount.Num()) // Reach Max Stage
		{
			StopGrowthTick();
		}
		else
		{
			OnGrowthStageIncrease(1);
		}
	}
}

// Called when the game starts or when spawned
void ACropEntityActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACropEntityActor::OnGrowthStageIncrease(int32 DeltaStage)
{
	CurrentStage = CurrentStage + DeltaStage;
	CurrentStageCount = 0;
	CropMesh->SetStaticMesh(CropData.CropStageMesh.Find(CurrentStage)->Get());
}

// Called every frame
void ACropEntityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
