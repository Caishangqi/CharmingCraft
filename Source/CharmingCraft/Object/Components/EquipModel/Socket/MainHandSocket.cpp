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
	UE_LOG(LogTemp, Warning, TEXT("UMainHandSocket Is %p"), *MainHandSocket->GetFullName());
}

void UMainHandSocket::BindSocket()
{
	Super::BindSocket();
	TArray<USceneComponent*> ChildComponents;
	SkeletalMeshComponent->GetChildrenComponents(true, ChildComponents);
	for (USceneComponent* Child : ChildComponents)
	{
		if (Child && Child->GetName() == "MainHand")
		{
			MainHandSocket = Cast<UStaticMeshComponent>(Child);
			break;
		}
	}
}
