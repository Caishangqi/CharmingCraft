// Fill out your copyright notice in the Description page of Project Settings.


#include "Entry.h"
#include "EngineUtils.h"
#include "LevelTargetPoint.h"
#include "Engine/TargetPoint.h"


// Sets default values for this component's properties
UEntry::UEntry()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bPostEntryOriginVisibility = false;
}


// Called when the game starts
void UEntry::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEntry::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEntry::TeleportToDestination(APawn* TargetPawn)
{
	for (TActorIterator<ALevelTargetPoint> It(GetWorld(), ALevelTargetPoint::StaticClass()); It; ++It)
	{
		ALevelTargetPoint* TargetActor = *It;
		if (TargetActor->GetActorLabel() == DestinationName)
		{
			TargetPawn->TeleportTo(TargetActor->GetActorLocation(), FRotator3d(0, 0, 0), false, true);
			return true;
		}
	}
	return false;
}
