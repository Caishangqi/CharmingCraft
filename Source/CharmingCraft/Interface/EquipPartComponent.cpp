// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartComponent.h"

// Sets default values for this component's properties
UEquipPartComponent::UEquipPartComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/* 初始化 */
	ItemNeedToForge = 0;
}


// Called when the game starts
void UEquipPartComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UEquipPartComponent::UpdateRenderMesh(FString& NewComponentMaterialText)
{
}


// Called every frame
void UEquipPartComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
