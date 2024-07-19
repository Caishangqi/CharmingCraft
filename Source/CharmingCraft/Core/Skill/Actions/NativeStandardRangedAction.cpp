// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeStandardRangedAction.h"
#include "CharmingCraft/Core/Builds/Interface/OccludeObject.h"
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
	// 设置射线投射的参数
	FCollisionQueryParams Params;

	// 添加要查找的碰撞类型
	FCollisionObjectQueryParams ObjectType;
	ObjectType.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectType.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1); // 这里查找Occlude 碰撞类型 (自定义的)

	Params.bTraceComplex = true; // 使用复杂碰撞进行射线投射
	Params.AddIgnoredActor(Instigator);
	TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Instigator->GetController());
	if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		TArray<FHitResult> OutHits;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector End = CameraLocation + (WorldDirection * 10000.f);
		bool bHit = GetWorld()->LineTraceMultiByObjectType(OutHits, CameraLocation, End, ObjectType, Params);
		if (bHit)
		{
			for (FHitResult OutHit : OutHits)
			{
				// 检查击中的Component是否是Occlude组件
				if (OutHit.GetComponent()->Implements<UOccludeObject>())
				{
					bool bIsOccludeObjectHit = IOccludeObject::Execute_GetIsOccluded(OutHit.GetComponent());
					// 如果是Occlude组件检查这个组件是否现在遮挡玩家视野
					if (bIsOccludeObjectHit)
					{
						// 如果正在遮挡玩家视野我们希望射线穿过这个Component去寻找下一个位置
						continue;
					}
					else
					{
						return OutHit.Location; // 如果没有遮挡当作正常墙体/目标并返回位置
					}
				}
				return OutHit.Location;
			}
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
