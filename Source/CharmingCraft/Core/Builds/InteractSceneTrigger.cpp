// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractSceneTrigger.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractSceneTrigger::AInteractSceneTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractSceneTrigger::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	if (EnableCameraFade)
	{
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
			0.1f, 1.0f, 0.05f, FColor::Black, false, true);
	}

	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Prepare Load Building Scene: %s"), *TargetLoadedLevel.LoadSynchronous()->GetMapName());

	FLevelStreamingDynamicResult LoadWorldInstanceOut = GetWorldManager_Implementation()->LoadWorldInstance(
		TargetLoadedLevel);
	LoadWorldInstanceOut.LoadedWorld->OnLevelShown.AddDynamic(this, &AInteractSceneTrigger::OnTargetLevelShown);
	InteractObject = Cast<APawn>(InstigatorPawn);
}

// Called when the game starts or when spawned
void AInteractSceneTrigger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractSceneTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AInteractSceneTrigger::OnTargetLevelShown()
{
	if (EnableCameraFade)
	{
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
			1.0f, 0.0f, 1.0f, FColor::Black);
	}
	GetGameEventHandler_Implementation()->OnLoadGameLevelCompleteEvent(this, TargetLoadedLevel.LoadSynchronous());
	if (InteractObject)
	{
		GetWorldManager_Implementation()->TeleportPlayerToWarpLocal(InteractObject, DestinationName);
		PostLevelCameraViewChange(); // Change Camera

		InteractObject = nullptr;
	}
	GetWorldManager_Implementation()->UnloadWorldInstance(UnloadedLevel.LoadSynchronous());
}

void AInteractSceneTrigger::PostLevelCameraViewChange()
{
	if (EnableChangeCameraView)
	{
		if (EnableCustomCameraView)
		{
			// TODO: EnableCustomCameraView
		}
		GetGameInstance_Implementation()->GetCameraManager()->SwitchPlayerCameraView(InteractObject, TargetCameraView);
	}
}

UCharmingCraftInstance* AInteractSceneTrigger::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UGameEventHandler* AInteractSceneTrigger::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}

UWorldManager* AInteractSceneTrigger::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
}
