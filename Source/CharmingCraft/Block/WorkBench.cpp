// Fill out your copyright notice in the Description page of Project Settings.


#include "WorkBench.h"

#include "../Object/Components/Container/WorkBenchComponent.h"

AWorkBench::AWorkBench()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WorkBenchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorkBenchMesh"));
	RootComponent = WorkBenchMesh;

	HologramMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HologramMesh"));
	HologramMesh->SetupAttachment(WorkBenchMesh);

	WorkBenchComponent = CreateDefaultSubobject<UWorkBenchComponent>(TEXT("WorkBenchComponent"));
}

void AWorkBench::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	UE_LOG(LogTemp, Warning, TEXT("Call Back from AWorkBench::Interact_Implementation"));
}
