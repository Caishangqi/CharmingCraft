// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEntityActorP5.h"

#include "Components/ArrowComponent.h"


// Sets default values
ASwordEntityActorP5::ASwordEntityActorP5()
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

	Blade->SetupAttachment(Sword);
	Fuller->SetupAttachment(Sword);
	Guard->SetupAttachment(Sword);
	Hilt->SetupAttachment(Sword);
	Pommel->SetupAttachment(Sword);


	EquipmentBottomArrow->SetupAttachment(Sword);
	EquipmentTopArrow->SetupAttachment(Sword);
	// Pitch(Green) Yaw(Blue) Roll(Red)
	EquipmentTopArrow->SetRelativeLocation(FVector(150.0f, 50.0f, 160.0f));
	EquipmentTopArrow->SetRelativeRotation(FRotator3d(-50.0f, 180.0f, 0.0f));
	EquipmentBottomArrow->SetRelativeLocation(FVector(45.0f, 50.0f, 40.0f));
	EquipmentBottomArrow->SetRelativeRotation(FRotator3d(50.0f, 0.0f, 0.0f));

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
void ASwordEntityActorP5::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwordEntityActorP5::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

