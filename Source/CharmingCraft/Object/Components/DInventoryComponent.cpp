// Fill out your copyright notice in the Description page of Project Settings.


#include "DInventoryComponent.h"

#include "DCharacter.h"
#include "DItemDataComponent.h"
#include "CharmingCraft/Controller/DPlayerAIController.h"
#include "CharmingCraft/Interface/DGameplayInterface.h"
#include "CharmingCraft/Interface/DItemInteractInterface.h"

// Sets default values for this component's properties
UDInventoryComponent::UDInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	// ...
}

void UDInventoryComponent::AddToInventory()
{
}

void UDInventoryComponent::RemoveFromInventory()
{
}


void UDInventoryComponent::OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator)
{
	if (TargetActor.Get()->GetComponentByClass(UDItemDataComponent::StaticClass()))
	{
		IDItemInteractInterface::Execute_Interact(
			TargetActor.Get()->GetComponentByClass(UDItemDataComponent::StaticClass()), Instigator);
	}

	UE_LOG(LogTemp, Warning, TEXT("Call Back from UDInventoryComponent::OnItemInteract"));
}

// Called when the game starts
void UDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// 注册事件
}


// Called every frame
void UDInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
