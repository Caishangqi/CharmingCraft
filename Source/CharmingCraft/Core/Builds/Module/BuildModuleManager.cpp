// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildModuleManager.h"

#include "CharmingCraft/Controller/DPlayerController.h"
#include "CharmingCraft/Core/Builds/Lib/BuildModuleLib.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/Meta/BlockMeta.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

UBuildModuleManager::UBuildModuleManager()
{
	LoadMaterialToPlaceValidation();
}

bool UBuildModuleManager::StartBuildPreviewTrace(UItemStack* PreviewItemStack, ACharacter* Instigator)
{
	if (PreviewItemStack)
	{
		CachedBuildItemStack = PreviewItemStack;
		BlockEntityActor = Cast<UBlockMeta>(PreviewItemStack->ItemMeta)->CreateBlockEntityActor(
			Instigator->GetWorld());
	}

	SaveBlockInteractProperties();	// Save InteractObject Data
	//	Settings that avoid player interact with block while building
	BlockEntityActor->bIsAllowToInteract = false;
	BlockEntityActor->bIsHighlighted = false;
	//	Enhance visual, set default VALID that show green grid
	BlockEntityActor->EnablePreviewScaleBox();
	BlockEntityActor->ChangeValidationCollidedType(EBuildCollidedType::VALID, PlaceValidation);

	TObjectPtr<UCharmingCraftInstance> GameInstance = Cast<UCharmingCraftInstance>(GetOuter());
	GameInstance->GetGameEventHandler()->OnBuildPreviewTraceEvent(CachedBuildItemStack, Instigator);
	TObjectPtr<ADPlayerController> PlayerController = Cast<ADPlayerController>(Instigator->GetController());

	// Initialize the preview block on player cursor
	bool bHit = PlayerController->
		GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	if (bHit)
	{
		BlockEntityActor->SetActorLocation(HitResult.Location);
		BlockEntityActor->DisableBlockCollision();
	}

	// Direct Linetrace

	// GetWorld()->GetTimerManager().SetTimer(InternalTimer, [this, PlayerController]()
	//                                        {
	// 	                                       bool bHit = PlayerController->
	// 		                                       GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	// 	                                       if (bHit)
	// 	                                       {
	// 		                                       // UE_LOG(LogChamingCraftCraftBuild, Display,
	// 		                                       //        TEXT("[📦]  BuildModuleManager Hit a Object\n"
	// 		                                       //         "		 [A] Actor Name =			%s\n"
	// 		                                       //         "		 [B] Is Collied =			%hhd"
	// 		                                       //        ), *HitResult.GetActor()->GetName(),
	// 		                                       //        BlockEntityActor->bIsCollied);
	// 		                                       if (HitResult.GetActor() != BlockEntityActor)
	// 		                                       {
	// 			                                       BlockEntityActor->SetActorLocation(
	// 				                                       UBuildModuleLib::SnapToGrid(HitResult.Location, GridSize));
	// 		                                       }
	// 	                                       }
	//                                        },
	//                                        UpdateTick, true);

	// Line Trace from camera

	GetWorld()->GetTimerManager().SetTimer(InternalTimer, [this, PlayerController]()
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		FVector WorldLocation, WorldDirection;
		if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
			// 沿着鼠标方向的射线的结束位置（你可以自定义射线长度）
			FVector End = CameraLocation + (WorldDirection * 10000.f);
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, End, ECC_WorldStatic);

			if (bHit)
			{
				if (HitResult.GetActor() != BlockEntityActor)
				{
					BlockEntityActor->SetActorLocation(
						UBuildModuleLib::SnapToGrid(HitResult.Location, GridSize));
					if (BlockEntityActor->bIsCollied)
					{
						BlockEntityActor->ChangeValidationCollidedType(EBuildCollidedType::COLLIDED, PlaceValidation);
					}
					else
					{
						BlockEntityActor->ChangeValidationCollidedType(EBuildCollidedType::VALID, PlaceValidation);
					}
				}
			}
		}
	}, UpdateTick, true);

	return true;
}

bool UBuildModuleManager::PlaceBuildPreview(ACharacter* Instigator)
{
	if (CachedBuildItemStack && BlockEntityActor && !BlockEntityActor->bIsCollied)
	{
		TObjectPtr<UCharmingCraftInstance> GameInstance = Cast<UCharmingCraftInstance>(GetOuter());
		GameInstance->GetGameEventHandler()->OnBlockPlaceEvent(CachedBuildItemStack, BlockEntityActor, Instigator);
		LoadBlockInteractProperties(BlockEntityActor, PlaceValidation);
		GetWorld()->GetTimerManager().PauseTimer(InternalTimer);
		BlockEntityActor->DisablePreviewScaleBox();
		BlockEntityActor->EnableBlockCollision();
		BlockEntityActor->bIsPlaced = true;
		TObjectPtr<ADCharacter> Player = Cast<ADCharacter>(Instigator);
		if (Player->InventoryComponent->RemoveInventoryByItemStack(CachedBuildItemStack, 1) != 0)
		{
			BlockEntityActor = nullptr;
			StartBuildPreviewTrace(CachedBuildItemStack, Instigator);
			return true;
		}
		CachedBuildItemStack = nullptr;
		BlockEntityActor = nullptr;
		return true;
	}


	return false;
}

void UBuildModuleManager::StopBuildPreview()
{
	GetWorld()->GetTimerManager().PauseTimer(InternalTimer);
	if (BlockEntityActor)
	{
		BlockEntityActor->Destroy();
	}
}

void UBuildModuleManager::LoadMaterialToPlaceValidation()
{
	// /Script/Engine.MaterialInstanceConstant'/Game/CharmingCraft/Block/Module/Material/M_CubeCollisionWarning.M_CubeCollisionWarning' CollidedMatFinder ValidMatFinder
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> ValidMatFinder(TEXT(
		"/Script/Engine.MaterialInstanceConstant'/Game/CharmingCraft/Block/Module/Material/M_CubeCollisionValid.M_CubeCollisionValid'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> CollidedMatFinder(
		TEXT(
			"/Script/Engine.MaterialInstanceConstant'/Game/CharmingCraft/Block/Module/Material/M_CubeCollisionCollided.M_CubeCollisionCollided'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> WarningMatFinder(
		TEXT(
			"/Script/Engine.MaterialInstanceConstant'/Game/CharmingCraft/Block/Module/Material/M_CubeCollisionWarning.M_CubeCollisionWarning'"));

	if (CollidedMatFinder.Succeeded()) PlaceValidation.ColliedMaterial = CollidedMatFinder.Object;
	if (ValidMatFinder.Succeeded()) PlaceValidation.ValidMaterial = ValidMatFinder.Object;
	if (WarningMatFinder.Succeeded()) PlaceValidation.WarningMaterial = WarningMatFinder.Object;
}

void UBuildModuleManager::SaveBlockInteractProperties()
{
	PlaceValidation.bIsHighlighted = BlockEntityActor->bIsHighlighted;
	PlaceValidation.bIsAllowToInteract = BlockEntityActor->bIsAllowToInteract;
}

void UBuildModuleManager::LoadBlockInteractProperties(ABlockEntityActor* BlockActor, const FPlaceValidation& Data)
{
	BlockActor->bIsHighlighted = Data.bIsHighlighted;
	BlockActor->bIsAllowToInteract = Data.bIsAllowToInteract;
}
