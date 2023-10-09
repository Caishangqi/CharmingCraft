// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSocket.h"

UCharacterSocket* UCharacterSocket::Initialize(ADCharacter* Player)
{
	this->Owner = Player;
	return this;
}

void UCharacterSocket::UpdateRender()
{
}
