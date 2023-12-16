// Fill out your copyright notice in the Description page of Project Settings.


#include "Build.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ABuild::ABuild()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent Mesh"));
	RootComponent = SceneComponent;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
	BuildingMesh->SetupAttachment(SceneComponent);

	BuildingEntry = CreateDefaultSubobject<UEntry>(TEXT("MainEntry"));
	BuildingEntry->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ABuild::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABuild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
