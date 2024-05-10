// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractSceneTrigger.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractSceneTrigger::AInteractSceneTrigger(): TargetCameraView()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractSceneTrigger::Interact_Implementation(APawn* InstigatorPawn)
{
	InteractObject = Cast<APawn>(InstigatorPawn);
	if (EnableCameraFade)
	{
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
			0.1f, 1.0f, 0.05f, FColor::Black, false, true);
	}
	if (bIsASceneTravel)
	{
		UE_LOG(LogChamingCraftWorld, Warning, TEXT("[🌍]  Prepare Load Building Scene: %s"),
		       *TargetLoadedLevel.LoadSynchronous()->GetName());
		FLevelStreamingDynamicResult LoadWorldInstanceOut = GetWorldManager_Implementation()->LoadWorldInstance(
			TargetLoadedLevel);


		if (!LoadWorldInstanceOut.LoadedWorld->OnLevelShown.IsAlreadyBound(
			this, &AInteractSceneTrigger::OnTargetLevelShown))
		{
			LoadWorldInstanceOut.LoadedWorld->OnLevelShown.AddDynamic(this, &AInteractSceneTrigger::OnTargetLevelShown);
		}
	}
	else
	{
		GetWorldManager_Implementation()->TeleportPlayerToWarp(InteractObject, DestinationName);
	}
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
	GetGameEventHandler_Implementation()->OnLoadGameLevelCompleteEvent(this, TargetLoadedLevel.LoadSynchronous());
	if (InteractObject)
	{
		FTimerHandle InOutHandle;
		GetWorld()->GetTimerManager().SetTimer(InOutHandle, [this]()
		{
			GetWorldManager_Implementation()->TravelPlayerToScene(InteractObject, TargetLoadedLevel, DestinationName,
			                                                      bResetSceneData);
			InteractObject->Controller->StopMovement();
			PostLevelCameraViewChange(); // Change Camera

			InteractObject = nullptr;
			FLevelStreamingDynamicResult UnLoadWorldInstanceOut = GetWorldManager_Implementation()->UnloadWorldInstance(
				UnloadedLevel.LoadSynchronous());
			if (UnLoadWorldInstanceOut.IsSuccess)
			{
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
					1.0f, 0.0f, 1.5f, FColor::Black);
			}
		}, 1, false);
	}
}

void AInteractSceneTrigger::OnTargetLevelHidden()
{
	UE_LOG(LogChamingCraftWorld, Warning, TEXT("[🌍]  Execute On Level Hiden Callback: %s"),
	       *UnloadedLevel.LoadSynchronous()->GetName());
	if (EnableCameraFade)
	{
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
			1.0f, 0.0f, 1.0f, FColor::Black);
	}
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
