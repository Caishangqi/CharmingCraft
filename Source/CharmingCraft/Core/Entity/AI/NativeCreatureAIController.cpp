// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeCreatureAIController.h"
#include "CharmingCraft/Core/Entity/Creature/NativeCreature.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ANativeCreatureAIController::ANativeCreatureAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANativeCreatureAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ANativeCreatureAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (Cast<ANativeCreature>(InPawn)->BehaviourTree)
	{
		RunBehaviorTree(Cast<ANativeCreature>(InPawn)->BehaviourTree);
	}
}

// Called every frame
void ANativeCreatureAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UCharmingCraftInstance* ANativeCreatureAIController::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UGameEventHandler* ANativeCreatureAIController::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}
