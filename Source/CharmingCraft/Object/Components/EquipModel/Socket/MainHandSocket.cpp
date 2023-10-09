// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHandSocket.h"

#include "DCharacter.h"

UMainHandSocket::UMainHandSocket()
{
	SocketName = "MainHand";
	SocketIndex = 0;
}

void UMainHandSocket::UpdateRender()
{
	Super::UpdateRender();
	UE_LOG(LogTemp, Warning, TEXT("UMainHandSocket::UpdateRender()"));
	UE_LOG(LogTemp, Warning, TEXT("UMainHandSocket Owner Is %p"), *Owner->GetName());
}
