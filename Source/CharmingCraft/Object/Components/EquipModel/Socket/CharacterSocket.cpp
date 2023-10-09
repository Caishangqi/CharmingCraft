// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSocket.h"

#include "DCharacter.h"

UCharacterSocket* UCharacterSocket::Initialize(ADCharacter* Player)
{
	this->Owner = Player;
	if (this->Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not NULL"));
		SkeletalMeshComponent = Owner->GetMesh();
		BindSocket();
	}
	return this;
}

void UCharacterSocket::UpdateRender()
{
}

void UCharacterSocket::BindSocket()
{
}
