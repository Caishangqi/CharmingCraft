// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "DCharacter.h"
#include "EngineUtils.h"
#include "LevelWarpPoint.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADoor::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);


	ADCharacter* Player = Cast<ADCharacter>(InstigatorPawn);
	UGameplayStatics::GetPlayerCameraManager(Player->GetWorld(), 0)->StartCameraFade(
		0.0f, 1.0f, 1.0f, FColor::Black);
	UGameplayStatics::LoadStreamLevel(Player->GetWorld(), FName("WorldSpawn"), true, false, FLatentActionInfo());
	if (bTeleportToDefaultExit)
	{
		if (CanTeleportToDestination(InstigatorPawn))
		{
			TeleportToDestination(InstigatorPawn, DoorInternalCacheTarget);
			FLatentActionInfo LatentActionInfo;
			LatentActionInfo.CallbackTarget = this;
			LatentActionInfo.ExecutionFunction = "PostDoorInteract"; // 延迟后要调用的函数名
			LatentActionInfo.Linkage = 0;
			LatentActionInfo.UUID = 1;
			UGameplayStatics::GetPlayerCameraManager(Player->GetWorld(), 0)->StartCameraFade(
				1.0f, 0.0f, 2.0f, FColor::Black);
			Player->SetCameraView();
			UGameplayStatics::UnloadStreamLevel(this->GetWorld(), FName("SmallPubInterior"), LatentActionInfo, false);
		}
		else
		{
			UGameplayStatics::UnloadStreamLevel(this->GetWorld(), FName("WorldSpawn"), FLatentActionInfo(), false);
		}
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADoor::CanTeleportToDestination(APawn* TargetPawn)
{
	for (TActorIterator<ALevelWarpPoint> It(GetWorld(), ALevelWarpPoint::StaticClass()); It; ++It)
	{
		ALevelWarpPoint* TargetActor = *It;
		if (TargetActor->TargetName == DestinationName)
		{
			DoorInternalCacheTarget = TargetActor;
			return true;
		}
	}
	return false;
}

bool ADoor::TeleportToDestination(APawn* TargetPawn, AActor* Actor)
{
	return TargetPawn->TeleportTo(Actor->GetActorLocation(), FRotator3d(0, 0, 0), false, false);
}

void ADoor::PostDoorInteract(APawn* TargetPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("ADoor::PostDoorInteract"));
}
