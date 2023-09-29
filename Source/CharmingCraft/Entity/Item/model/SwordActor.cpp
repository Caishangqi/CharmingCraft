// Fill out your copyright notice in the Description page of Project Settings.
#include "SwordActor.h"

// Sets default values
ASwordActor::ASwordActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sword = CreateDefaultSubobject<UStaticMeshComponent>("Sword Root");
	Blade = CreateDefaultSubobject<UStaticMeshComponent>("Blade");
	Fuller = CreateDefaultSubobject<UStaticMeshComponent>("Fuller");
	Guard = CreateDefaultSubobject<UStaticMeshComponent>("Guard");
	Hilt = CreateDefaultSubobject<UStaticMeshComponent>("Hilt");
	Pommel = CreateDefaultSubobject<UStaticMeshComponent>("Pommel");

	Blade->SetupAttachment(Sword);
	Fuller->SetupAttachment(Sword);
	Guard->SetupAttachment(Sword);
	Hilt->SetupAttachment(Sword);
	Pommel->SetupAttachment(Sword);

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
