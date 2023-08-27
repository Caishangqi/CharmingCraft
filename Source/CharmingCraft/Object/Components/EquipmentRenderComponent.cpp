// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentRenderComponent.h"

#include "DCharacter.h"
#include "EquipmentManagerComponent.h"

// Sets default values for this component's properties
UEquipmentRenderComponent::UEquipmentRenderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	UE_LOG(LogTemp, Warning, TEXT("UEquipmentRenderComponent Initialize"));
	UEquipmentManagerComponent* EquipmentManagerComponent = Cast<UEquipmentManagerComponent>(GetOuter());
	//EquipmentManagerComponent->HelmetSlot
}


// Called when the game starts
void UEquipmentRenderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEquipmentRenderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
