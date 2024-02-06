// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSocket.h"

#include "DCharacter.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Object/Components/EquipModel/EquipmentManagerComponent.h"
#include "CharmingCraft/Object/Components/EquipModel/EquipmentRenderComponent.h"

UCharacterSocket* UCharacterSocket::Initialize(ADCharacter* Player, int32 Index)
{
	this->Owner = Player;
	this->SocketIndex = Index;
	if (this->Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not NULL"));
		SkeletalMeshComponent = Owner->GetMesh();
	}

	return this;
}

void UCharacterSocket::UpdateRender()
{
	BindSocket();
	SocketItem = this->Owner->EquipmentManagerComponent->Inventory[SocketIndex];
}

void UCharacterSocket::BindSocket()
{
	UE_LOG(LogTemp, Warning, TEXT("(!) SocketIndex: %d"), SocketIndex);
}
