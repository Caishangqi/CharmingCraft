// Fill out your copyright notice in the Description page of Project Settings.


#include "DItemDataComponent.h"

// Sets default values for this component's properties
UDItemDataComponent::UDItemDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDItemDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
	
}


// Called every frame
void UDItemDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

