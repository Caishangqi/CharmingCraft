// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceEntityActor.h"
#include "Components/BoxComponent.h"


// Sets default values
AResourceEntityActor::AResourceEntityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;
	HitBox->SetupAttachment(RootComponent);

	// Data
	CurrentStage = 0;
}

// Called when the game starts or when spawned
void AResourceEntityActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AResourceEntityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
