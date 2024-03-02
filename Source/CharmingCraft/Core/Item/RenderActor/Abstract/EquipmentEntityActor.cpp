// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentEntityActor.h"

#include "Components/ArrowComponent.h"


// Sets default values
AEquipmentEntityActor::AEquipmentEntityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	/* For Attack Line Tracing*/
	EquipmentTopArrow = CreateDefaultSubobject<UArrowComponent>("SwordTopArrow");
	EquipmentTopArrow->SetupAttachment(RootComponent);
	EquipmentTopArrow->SetHiddenInGame(false);
	EquipmentBottomArrow = CreateDefaultSubobject<UArrowComponent>("SwordBottomArrow");
	EquipmentBottomArrow->SetupAttachment(RootComponent);
	EquipmentBottomArrow->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void AEquipmentEntityActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEquipmentEntityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
