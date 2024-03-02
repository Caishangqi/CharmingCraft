// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldStaticBiome.h"


// Sets default values
AWorldStaticBiome::AWorldStaticBiome()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWorldStaticBiome::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorldStaticBiome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
