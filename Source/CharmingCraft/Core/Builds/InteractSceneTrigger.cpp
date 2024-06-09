// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractSceneTrigger.h"

#include "CraftWorldWarpPoint.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractSceneTrigger::AInteractSceneTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractSceneTrigger::Interact_Implementation(APawn* InstigatorPawn)
{
	InteractObject = InstigatorPawn;
	if (bIsASceneTravel)
	{
		//UE_LOG(LogChamingCraftWorld, Error, TEXT("AInteractSceneTrigger::Interact_Implementation"))
		TObjectPtr<UNativeCraftWorld> CraftWorld = UCoreComponents::GetWorldManager(this)->LoadCraftWorldInMemory(
			TargetCraftWorld);
		// TODO: Find why CraftWorld->OnWarpDataUpdate.AddDynamic not invoke
		CraftWorld->OnWarpDataUpdateInternal.AddLambda([this,CraftWorld](UNativeCraftWorld*, ACraftWorldWarpPoint*)
		{
			UCoreComponents::GetWorldManager(this->InteractObject)->TeleportPlayerToWarp(
				this->InteractObject, DestinationName);
			
			if (EnableCameraFade)
			{
				UGameplayStatics::GetPlayerCameraManager(InteractObject, 0)->StartCameraFade
				(0.8f, 0.0f, 2.0f, FColor::Black, false,
				 true);
			}
			CraftWorld->OnWarpDataUpdateInternal.Clear();
			CraftWorld->OnWarpDataUpdate.Clear();
		});

		//CraftWorld->OnWarpDataUpdate.AddDynamic(this, &AInteractSceneTrigger::OnCraftWorldWarpLoaded);

		UCoreComponents::GetWorldManager(this)->ShownCraftWorld(CraftWorld);
		CraftWorld->AddPlayerToWorldPlayerList(static_cast<ACharacter*>(InteractObject));

		if (EnableCameraFade)
		{
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade
			(0.5f, 1.0f, 1.0f, FColor::Black, false,
			 true);
		}
	}
	else
	{
		GetWorldManager_Implementation()->TravelPlayerToWarp(InteractObject, DestinationName);
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
