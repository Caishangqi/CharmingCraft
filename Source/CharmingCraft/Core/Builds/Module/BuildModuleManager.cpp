// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildModuleManager.h"
#include "CharmingCraft/Core/Builds/Interface/UBreakable.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "CharmingCraft/Controller/DPlayerController.h"
#include "CharmingCraft/Core/Builds/Block/FrameActor.h"
#include "CharmingCraft/Core/Builds/Lib/BuildModuleLib.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/Meta/BlockMeta.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Kismet/GameplayStatics.h"

UBuildModuleManager::UBuildModuleManager()
{
	LoadMaterialToPlaceValidation();
	static ConstructorHelpers::FObjectFinder<UBlueprint> FrameActor(
		TEXT("/Script/Engine.Blueprint'/Game/CharmingCraft/Block/Module/FrameActor.FrameActor'"));
	if (FrameActor.Succeeded())
	{
		// 蓝图加载成功，你可以使用ActorBlueprint.Object来做进一步的操作，比如创建Actor实例
		FrameActorClass = FrameActor.Object->GeneratedClass;
		// 然后你可以使用ActorClass来在游戏世界中创建这个Actor的实例
	}
}

bool UBuildModuleManager::StartBuildPreviewTrace(UItemStack* PreviewItemStack, ACharacter* Instigator)
{
	if (BlockEntityActor)
	{
		BlockEntityActor->Destroy();
		CachedBuildItemStack = PreviewItemStack;
	}

	if (PreviewItemStack)
	{
		CachedBuildItemStack = PreviewItemStack;
		BlockEntityActor = Cast<UBlockMeta>(PreviewItemStack->ItemMeta)->CreateBlockEntityActor(
			Instigator->GetWorld());
	}

	if (PreviewItemStack && CachedBuildItemStack)
	{
		SaveBlockInteractProperties(); // Save InteractObject Data
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
							BlockEntityActor->ChangeValidationCollidedType(
								EBuildCollidedType::COLLIDED, PlaceValidation);
						}
						else
						{
							BlockEntityActor->ChangeValidationCollidedType(EBuildCollidedType::VALID, PlaceValidation);
						}
					}
				}
			}
		}, UpdateTick, true);
	}


	return true;
}

bool UBuildModuleManager::StartBreakPreviewTrace(ACharacter* Instigator)
{
	if (FrameActorClass)
	{
		FTransform DefaultTransform;
		HighlightFrameActor = Cast<AFrameActor>(
			UGameplayStatics::BeginDeferredActorSpawnFromClass(Instigator->GetWorld(),
			                                                   FrameActorClass,
			                                                   DefaultTransform));
		UGameplayStatics::FinishSpawningActor(HighlightFrameActor, DefaultTransform);
		HighlightFrameActor->CurrentFrameActorType = EFrameType::DESTROY;
		HighlightFrameActor->BuildModuleManager = this;
		TObjectPtr<ADPlayerController> PlayerController = Cast<ADPlayerController>(Instigator->GetController());

		GetWorld()->GetTimerManager().SetTimer(InternalTimer, [this, PlayerController]()
		                                       {
			                                       bool bHit = PlayerController->
				                                       GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
			                                       if (bHit)
			                                       {
				                                       if (HitResult.GetActor() != HighlightFrameActor)
				                                       {
					                                       HighlightFrameActor->SetActorLocation(
						                                       UBuildModuleLib::SnapToGrid(
							                                       HitResult.Location, GridSize));
				                                       }
			                                       }
		                                       },
		                                       UpdateTick, true);
	}

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
		IBreakableInterface::Execute_OnBlockPlace(BlockEntityActor, Instigator, BlockEntityActor);
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

bool UBuildModuleManager::BreakBlockPreview(ACharacter* Instigator)
{
	if (HighlightFrameActor && HighlightFrameActor->ColliedResult.ColliedActor != nullptr)
	{
		if (HighlightFrameActor->ColliedResult.bIsValidCollied)
		{
			AActor* ColliedActor = HighlightFrameActor->ColliedResult.ColliedActor;
			IBreakableInterface::Execute_OnBlockBreak(ColliedActor, Instigator, ColliedActor);
			HighlightFrameActor->ColliedResult.ColliedActor = nullptr;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void UBuildModuleManager::StopBuildPreview()
{
	GetWorld()->GetTimerManager().PauseTimer(InternalTimer);
	if (BlockEntityActor)
	{
		BlockEntityActor->Destroy();
		BlockEntityActor = nullptr;
	}
}

void UBuildModuleManager::StopBreakPreview()
{
	GetWorld()->GetTimerManager().PauseTimer(InternalTimer);
	if (HighlightFrameActor)
	{
		HighlightFrameActor->Destroy();
		HighlightFrameActor = nullptr;
	}
}

void UBuildModuleManager::OnPlaceModeChange(ACharacter* Instigator, EBuildMode ToMode)
{
	if (CurrentBuildMode == EBuildMode::BREAK)
	{
		CurrentBuildMode = EBuildMode::PLACE;
		Cast<UCharmingCraftInstance>(GetOuter())->GetGameEventHandler()->OnPlaceModeChangeEvent(
			Instigator, CurrentBuildMode);
		StopBreakPreview();
		StartBuildPreviewTrace(CachedBuildItemStack, Instigator);
		return;
	}
	if (CurrentBuildMode == EBuildMode::PLACE)
	{
		CurrentBuildMode = EBuildMode::BREAK;
		Cast<UCharmingCraftInstance>(GetOuter())->GetGameEventHandler()->OnPlaceModeChangeEvent(
			Instigator, CurrentBuildMode);
		StopBuildPreview();
		StartBreakPreviewTrace(Instigator);
		return;
	}
	return;
}

void UBuildModuleManager::RotatePreviewBlockLeft()
{
	if (BlockEntityActor)
	{
		// //(Pitch = 0.000000, Yaw = 17.999950, Roll = 0.000000)
		FRotator ActorRotation = BlockEntityActor->GetActorRotation();
		ActorRotation.Yaw += 90.0f;
		BlockEntityActor->SetActorRotation(ActorRotation);
		BlockEntityActor->SetActorLocation(UBuildModuleLib::SnapToGrid(HitResult.Location, GridSize));
	}
}

void UBuildModuleManager::RotatePreviewBlockRight()
{
	if (BlockEntityActor)
	{
		// //(Pitch = 0.000000, Yaw = 17.999950, Roll = 0.000000)
		FRotator ActorRotation = BlockEntityActor->GetActorRotation();
		ActorRotation.Yaw -= 90.0f;
		BlockEntityActor->SetActorRotation(ActorRotation);
		BlockEntityActor->SetActorLocation(UBuildModuleLib::SnapToGrid(HitResult.Location, GridSize));
	}
}

void UBuildModuleManager::RestToDefault()
{
	if (BlockEntityActor)
	{
		BlockEntityActor->Destroy();
	}
	if (HighlightFrameActor)
	{
		HighlightFrameActor->Destroy();
	}
	if (CachedBuildItemStack)
	{
		CachedBuildItemStack = nullptr;
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
