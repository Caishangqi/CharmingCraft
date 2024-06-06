// Fill out your copyright notice in the Description page of Project Settings.


#include "VolumeSceneTriggerComponent.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "EngineUtils.h"
#include "CraftWorldWarpPoint.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UVolumeSceneTriggerComponent::UVolumeSceneTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bPostEntryOriginVisibility = false;
	SetGenerateOverlapEvents(true);
}


// Called when the game starts
void UVolumeSceneTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (!OnComponentBeginOverlap.IsAlreadyBound(this, &UVolumeSceneTriggerComponent::OnOverlapBegin))
	{
		OnComponentBeginOverlap.AddDynamic(this, &UVolumeSceneTriggerComponent::OnOverlapBegin);
	}
	// ...
}


// Called every frame
void UVolumeSceneTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UVolumeSceneTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp,
                                                  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[🌍]  Prepare Load Building Scene: %s"), *TargetLoadedLevel.LoadSynchronous()->GetMapName());
	if (OtherActor->IsA(ANativePlayerCharacter::StaticClass()))
	{
		OverlappedActor = Cast<APawn>(OtherActor);
		if (bIsASceneTravel)
		{
			FCharmingCraftWorld LoadWorldInstanceOut = GetWorldManager_Implementation()->LoadWorldInstance(
				TargetLoadedLevel);
			if (EnableCameraFade)
			{
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
					0.1f, 1.0f, 1.0f, FColor::Black, false, true);
			}
			LoadWorldInstanceOut.GamePlayWorld->OnLevelShown.AddDynamic(
				this, &UVolumeSceneTriggerComponent::OnTargetLevelShown);
		}
		else
		{
			GetWorldManager_Implementation()->TravelPlayerToWarp(OverlappedActor, DestinationName);
		}
	}
}

void UVolumeSceneTriggerComponent::OnTargetLevelShown()
{
	GetGameEventHandler_Implementation()->OnLoadGameLevelCompleteEvent(this, TargetLoadedLevel.LoadSynchronous());

	if (OverlappedActor)
	{
		FTimerHandle InOutHandle;

		GetWorld()->GetTimerManager().SetTimer(InOutHandle, [this]()
		                                       {
			                                       GetWorldManager_Implementation()->TravelPlayerToScene(
				                                       OverlappedActor, TargetLoadedLevel, DestinationName,
				                                       bResetSceneData);
			                                       PostLevelCameraViewChange(); // Change Camera
			                                       OverlappedActor->Controller->StopMovement();
			                                       if (EnableCameraFade)
			                                       {
				                                       UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->
					                                       StartCameraFade(
						                                       1.0f, 0.0f, 1.0f, FColor::Black);
			                                       }
			                                       //OverlappedActor = nullptr;
			                                       GetWorldManager_Implementation()->UnloadWorldInstance(UnloadedLevel);
		                                       },
		                                       1, false);
	}
}

void UVolumeSceneTriggerComponent::OnTravelToDestination()
{
}

void UVolumeSceneTriggerComponent::PostLevelCameraViewChange()
{
	if (EnableChangeCameraView)
	{
		if (EnableCustomCameraView)
		{
			// TODO: EnableCustomCameraView
		}
		GetGameInstance_Implementation()->GetCameraManager()->SwitchPlayerCameraView(OverlappedActor, TargetCameraView);
	}
}

UCharmingCraftInstance* UVolumeSceneTriggerComponent::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UGameEventHandler* UVolumeSceneTriggerComponent::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}

UWorldManager* UVolumeSceneTriggerComponent::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
}
