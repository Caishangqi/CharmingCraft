// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHandSocket.h"
#include "DCharacter.h"
#include "../Object/Components/EquipModel/EquipmentRenderComponent.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Object/Components/ItemStack.h"
#include "CharmingCraft/Object/Components/EquipModel/EquipmentManagerComponent.h"
#include "Kismet/GameplayStatics.h"

UMainHandSocket::UMainHandSocket(): MainHandSocket(nullptr), AttachedActor(nullptr)
{
	SocketName = "MainHand";
	SocketIndex = 0;
}

void UMainHandSocket::UpdateRender()
{
	Super::UpdateRender();
	UE_LOG(LogTemp, Warning, TEXT("UMainHandSocket::UpdateRender()"));
	if (SocketItem == nullptr)
	{
		if (AttachedActor)
		{
			AttachedActor->Destroy();
		}
	}
	else
	{
		if (SocketItem->ItemMeta->IsA(UWeaponMeta::StaticClass()))
		{
			UWeaponMeta* WeaponMeta = Cast<UWeaponMeta>(SocketItem->ItemMeta);
			FTransform DefaultTransform;
			AttachedActor = Cast<AActor>(
				UGameplayStatics::BeginDeferredActorSpawnFromClass(this,
				                                                   WeaponMeta->WeaponActor, DefaultTransform));
			WeaponMeta->AssembleComponent(AttachedActor);
			UGameplayStatics::FinishSpawningActor(AttachedActor, DefaultTransform);
			if (MainHandSocket)
			{
				UE_LOG(LogTemp, Warning, TEXT("(+) Bind Actor to MainHand"));
				AttachedActor->AttachToComponent(MainHandSocket, FAttachmentTransformRules::KeepRelativeTransform);
			}
		}
	}
}

void UMainHandSocket::BindSocket()
{
	if (MainHandSocket == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("(!) UMainHandSocket::BindSocket()"));
		Super::BindSocket();
		TArray<USceneComponent*> ChildComponents;
		ChildComponents = SkeletalMeshComponent->GetAttachChildren();
		for (USceneComponent* Child : ChildComponents)
		{
			if (Child && Child->GetName() == "MainHand")
			{
				MainHandSocket = Cast<UStaticMeshComponent>(Child);
				break;
			}
		}
	}
}
