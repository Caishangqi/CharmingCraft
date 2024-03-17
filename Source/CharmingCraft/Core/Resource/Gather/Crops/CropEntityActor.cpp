// Fill out your copyright notice in the Description page of Project Settings.


#include "CropEntityActor.h"


// Sets default values
ACropEntityActor::ACropEntityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CropMesh = CreateDefaultSubobject<UStaticMeshComponent>("Crop Mesh");
	CropMesh->SetRelativeLocation(FVector(0, 0, 0));
	CropMesh->SetupAttachment(RootComponent);
}

bool ACropEntityActor::OnBlockPlace_Implementation(AActor* Instigator, AActor* BlockPlaced)
{
	return Super::OnBlockPlace_Implementation(Instigator, BlockPlaced);
}

void ACropEntityActor::StopGrowthTick_Implementation()
{
}

void ACropEntityActor::StartGrowthTick_Implementation()
{
}

int32 ACropEntityActor::OnGrowthTick_Implementation()
{
	return CurrentStageCount;
}

// Called when the game starts or when spawned
void ACropEntityActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACropEntityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
