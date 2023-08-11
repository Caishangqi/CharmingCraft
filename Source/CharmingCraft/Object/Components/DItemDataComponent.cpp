// Fill out your copyright notice in the Description page of Project Settings.


#include "DItemDataComponent.h"

#include "DCharacter.h"
#include "DInventoryComponent.h"
#include "CharmingCraft/Object/Structs/FDItemStruct.h"

// Sets default values for this component's properties
UDItemDataComponent::UDItemDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDItemDataComponent::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("接口实现调用: UDItemDataComponent::Interact_Implementation"));

	const ADCharacter* Player = Cast<ADCharacter>(InstigatorPawn);
	if (Player->InventoryComponent->
	            AddToInventory(FString(ItemID.RowName.ToString()), Quantity).
	            bIsSuccess)
	{
		IDItemInteractInterface::Interact_Implementation(InstigatorPawn);
		GetOwner()->Destroy();
	}
	else

	{
		UE_LOG(LogTemp, Warning, TEXT("UDItemDataComponent::Interact_Implementation 存入背包失败"));
	}
}

// Called when the game starts
void UDItemDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
}


// Called every frame
void UDItemDataComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
