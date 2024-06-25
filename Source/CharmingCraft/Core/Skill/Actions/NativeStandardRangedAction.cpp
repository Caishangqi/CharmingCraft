// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeStandardRangedAction.h"
#include "../Core/Interact/Interface/DGameplayInterface.h"
#include "CharmingCraft/Core/Item/RenderActor/Abstract/EquipmentEntityActor.h"

UNativeStandardRangedAction::UNativeStandardRangedAction()
{
	SkillType = EItemDynamicSkillSlot::RIGHT_CLICK;
}

FVector UNativeStandardRangedAction::GetCastMouseLocation(APawn* Instigator)
{
	bool bUseNormalViewProject = true;
	FVector CameraLocation;
	FRotator CameraRotation;
	FVector WorldLocation, WorldDirection;
	FHitResult HitResult;
	// 设置射线投射的参数
	FCollisionQueryParams Params;
	Params.bTraceComplex = true; // 使用复杂碰撞进行射线投射
	Params.AddIgnoredActor(Instigator);
	TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Instigator->GetController());
	if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{

		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector End = CameraLocation + (WorldDirection * 10000.f);
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, End, ECC_WorldStatic, Params);
		if (bHit)
		{
			// AActor* HitActor = HitResult.GetActor();
			//
			// if (HitActor && HitActor->Implements<UMouseInteractInterface>())
			// {
			// 	// Add Additional 50 unit offset
			// 	return HitActor->GetActorLocation() + FVector(0,0,50);
			// }
			// else
			// {
			// 	return HitResult.Location;
			// }

			return HitResult.Location;
		}
		else
		{
			return WorldLocation;
		}
	}
	return WorldLocation;
}


void UNativeStandardRangedAction::StartAction_Implementation(APawn* Instigator)
{
	Super::StartAction_Implementation(Instigator);
}
