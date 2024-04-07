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

	BuildingExitPoint = CreateDefaultSubobject<UChildActorComponent>(TEXT("Building Default Exit Location"));
	BuildingExitPoint->SetupAttachment(SceneComponent);
	// 创建并附加MyCustomActor到MyChildComponent
}

// Called when the game starts or when spawned
void ABuild::BeginPlay()
{
	Super::BeginPlay();
	ALevelWarpPoint* ExitActor = GetWorld()->SpawnActor<ALevelWarpPoint>(ALevelWarpPoint::StaticClass());
	ExitActor->TargetName = BuildName + " Default Exit";
	if (ExitActor)
	{
		ExitActor->AttachToComponent(BuildingExitPoint, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

// Called every frame
void ABuild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
