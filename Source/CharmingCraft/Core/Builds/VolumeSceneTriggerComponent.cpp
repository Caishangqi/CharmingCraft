// Fill out your copyright notice in the Description page of Project Settings.


#include "VolumeSceneTriggerComponent.h"

#include "DCharacter.h"
#include "EngineUtils.h"
#include "SceneWarpPoint.h"
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
	if (OtherActor->IsA(ADCharacter::StaticClass()))
	{
		FLevelStreamingDynamicResult LoadWorldInstanceOut = GetWorldManager_Implementation()->LoadWorldInstance(
			TargetLoadedLevel);
		if (EnableCameraFade)
		{
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
				0.0f, 1.0f, 1.0f, FColor::Black, false, true);
		}
		LoadWorldInstanceOut.LoadedWorld->OnLevelShown.AddDynamic(
			this, &UVolumeSceneTriggerComponent::OnTargetLevelShown);
		OverlappedActor = Cast<APawn>(OtherActor);
	}
}

void UVolumeSceneTriggerComponent::OnTargetLevelShown()
{
	if (EnableCameraFade)
	{
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
			1.0f, 0.0f, 1.0f, FColor::Black);
	}
	GetGameEventHandler_Implementation()->OnLoadGameLevelCompleteEvent(this, TargetLoadedLevel.LoadSynchronous());
	GetWorldManager_Implementation()->UnloadWorldInstance(UnloadedLevel);
	if (OverlappedActor)
	{
		PostLevelCameraViewChange(); // Change Camera
		GetWorldManager_Implementation()->TeleportPlayerToWarpLocal(OverlappedActor, DestinationName);
		OverlappedActor->Controller->StopMovement();
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
			1.0f, 0.0f, 1.0f, FColor::Black);
		OverlappedActor = nullptr;
	}
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
