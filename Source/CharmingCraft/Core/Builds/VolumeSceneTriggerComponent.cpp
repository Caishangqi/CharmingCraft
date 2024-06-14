// Fill out your copyright notice in the Description page of Project Settings.
#include "VolumeSceneTriggerComponent.h"
#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "CraftWorldWarpPoint.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "CharmingCraft/Core/World/WorldManager.h"
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
	if (OtherActor->IsA(ANativePlayerCharacter::StaticClass()))
	{
		OverlappedActor = Cast<APawn>(OtherActor);
		if (bIsASceneTravel)
		{
			if (EnableCameraFade)
			{
				UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(
					1.0f, 1.0f, 1.0f, FColor::Black, false, true);
			}
			TObjectPtr<UNativeCraftWorld> CraftWorld = UCoreComponents::GetWorldManager(this)->
				LoadCraftWorldInMemory(
					TargetCraftWorld);
			CraftWorld->OnWarpDataUpdate.AddDynamic(this, &UVolumeSceneTriggerComponent::OnCraftWorldWarpLoaded);
			UCoreComponents::GetWorldManager(this)->ShownCraftWorld(CraftWorld);
			CraftWorld->AddPlayerToWorldPlayerList(static_cast<ACharacter*>(OverlappedActor));
		}
		else
		{
			GetWorldManager_Implementation()->TravelPlayerToWarp(OverlappedActor, DestinationName);
		}
	}
}

void UVolumeSceneTriggerComponent::OnCraftWorldWarpLoaded(UNativeCraftWorld* CraftWorld,
                                                          ACraftWorldWarpPoint* TargetCraftWorldWarpPoint)
{
	if (OverlappedActor)
	{
		if (TargetCraftWorldWarpPoint->TargetName == DestinationName)
		{
			UCoreComponents::GetWorldManager(TargetCraftWorldWarpPoint)->TeleportPlayerToWarp(
			OverlappedActor, DestinationName);
			CraftWorld->OnWarpDataUpdateInternal.Clear();
			CraftWorld->OnWarpDataUpdate.Clear();
		}
		
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
