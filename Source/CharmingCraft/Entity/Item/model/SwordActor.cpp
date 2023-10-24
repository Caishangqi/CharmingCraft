// Fill out your copyright notice in the Description page of Project Settings.
#include "SwordActor.h"

#include "Components/ArrowComponent.h"

// Sets default values
ASwordActor::ASwordActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Sword = CreateDefaultSubobject<UStaticMeshComponent>("Sword Root");
	Blade = CreateDefaultSubobject<UStaticMeshComponent>("Blade");
	Fuller = CreateDefaultSubobject<UStaticMeshComponent>("Fuller");
	Guard = CreateDefaultSubobject<UStaticMeshComponent>("Guard");
	Hilt = CreateDefaultSubobject<UStaticMeshComponent>("Hilt");
	Pommel = CreateDefaultSubobject<UStaticMeshComponent>("Pommel");
	/* For Attack Line Tracing*/
	SwordTopArrow = CreateDefaultSubobject<UArrowComponent>("SwordTopArrow");
	SwordTopArrow->SetHiddenInGame(false);
	SwordBottomArrow = CreateDefaultSubobject<UArrowComponent>("SwordBottomArrow");
	SwordBottomArrow->SetHiddenInGame(false);

	Blade->SetupAttachment(Sword);
	Fuller->SetupAttachment(Sword);
	Guard->SetupAttachment(Sword);
	Hilt->SetupAttachment(Sword);
	Pommel->SetupAttachment(Sword);


	SwordBottomArrow->SetupAttachment(Sword);
	SwordTopArrow->SetupAttachment(Sword);
	// Pitch(Green) Yaw(Blue) Roll(Red)
	SwordTopArrow->SetRelativeLocation(FVector(150.0f, 50.0f, 160.0f));
	SwordTopArrow->SetRelativeRotation(FRotator3d(-50.0f, 180.0f, 0.0f));
	SwordBottomArrow->SetRelativeLocation(FVector(45.0f, 50.0f, 40.0f));
	SwordBottomArrow->SetRelativeRotation(FRotator3d(50.0f, 0.0f, 0.0f));

	Sword->SetupAttachment(RootComponent);

	for (auto Component : GetComponents())
	{
		if (UStaticMeshComponent* SMComponent = Cast<UStaticMeshComponent>(Component))
		{
			// 设置 CustomDepth 通道 = true
			SMComponent->SetRenderCustomDepth(true);

			// 设置自定义深度模板值为 10
			SMComponent->SetCustomDepthStencilValue(10);

			// 设置碰撞为 NoCollision
			SMComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

// Called when the game starts or when spawned
void ASwordActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASwordActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
