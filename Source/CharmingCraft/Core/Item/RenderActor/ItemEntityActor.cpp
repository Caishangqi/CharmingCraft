// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntityActor.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AItemEntityActor::AItemEntityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>("ChildActorComponent");
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItemEntityActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemEntityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
