// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentRenderComponent.h"
#include "EquipmentManagerComponent.h"
#include "Socket/MainHandSocket.h"
#include "../Public/DCharacter.h"
// Sets default values for this component's properties
UEquipmentRenderComponent::UEquipmentRenderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MainHand = CreateDefaultSubobject<UStaticMeshComponent>("MainHand");
}


// Called when the game starts
void UEquipmentRenderComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UEquipmentRenderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentRenderComponent::UpdateRender(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("UEquipmentRenderComponent::UpdateRender(int32 %d)"), Index);
	PlayerSkeletonSocket[Index]->UpdateRender();
}

UEquipmentRenderComponent* UEquipmentRenderComponent::Initialize(int32 Size, ADCharacter* Player)
{
	this->Owner = Player;
	MainHand->SetupAttachment(this->Owner->GetMesh(), FName("Main_Hand_Socket"));

	PlayerSkeletonSocket.SetNumZeroed(Size);

	PlayerSkeletonSocket[0] = NewObject<UMainHandSocket>(this)->Initialize(this->Owner, 0);
	return this;
}
