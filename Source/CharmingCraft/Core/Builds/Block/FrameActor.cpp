// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameActor.h"

#include "Components/BoxComponent.h"


// Sets default values
AFrameActor::AFrameActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	FrameOutlineBox3D = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameOutlineBox3D"));
	FrameOutlineBox3D->SetupAttachment(RootComponent);
	FrameOutline2D = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameOutline2D"));
	FrameOutline2D->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->InitBoxExtent(FVector(48.0f, 48.0f, 48.0f));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeLocation(FVector(50, 50, 50));

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFrameActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AFrameActor::OnOverlapEnd);
}

void AFrameActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	// 处理开始重叠的逻辑
	if (OtherActor != this && OtherActor != nullptr)
	{
		ColliedActor = OtherActor;
	}
}

void AFrameActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex)
{
	ColliedActor = nullptr;
}

// Called when the game starts or when spawned
void AFrameActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFrameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFrameActor::SetFrameDestroyState_Implementation()
{
}
