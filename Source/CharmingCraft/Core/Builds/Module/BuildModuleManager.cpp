// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildModuleManager.h"

#include "CharmingCraft/Controller/DPlayerController.h"
#include "CharmingCraft/Core/Builds/Lib/BuildModuleLib.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/Meta/BlockMeta.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

bool UBuildModuleManager::StartBuildPreviewTrace(UItemStack* PreviewItemStack, ACharacter* Instigator)
{
	if (PreviewItemStack)
	{
		CachedBuildItemStack = PreviewItemStack;
		BlockEntityActor = Cast<UBlockMeta>(PreviewItemStack->ItemMeta)->CreateBlockEntityActor(
			Instigator->GetWorld());
	}

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

	GetWorld()->GetTimerManager().SetTimer(InternalTimer, [this, PlayerController]()
	                                       {
		                                       bool bHit = PlayerController->
			                                       GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
		                                       if (bHit)
		                                       {
			                                       // UE_LOG(LogChamingCraftCraftBuild, Display,
			                                       //        TEXT("[📦]  BuildModuleManager Hit a Object\n"
			                                       //         "		 [A] Actor Name =			%s"
			                                       //        ), *HitResult.GetActor()->GetName());
			                                       if (HitResult.GetActor() != BlockEntityActor)
			                                       {
				                                       BlockEntityActor->SetActorLocation(
					                                       UBuildModuleLib::SnapToGrid(HitResult.Location, GridSize));
			                                       }
		                                       }
	                                       },
	                                       UpdateTick, true);


	return true;
}

bool UBuildModuleManager::PlaceBuildPreview(ACharacter* Instigator)
{
	// UE_LOG(LogChamingCraftCraftBuild, Display,
	//        TEXT("[📦]  TEST ==================================="
	//
	//        ));
	if (CachedBuildItemStack && BlockEntityActor)
	{
		TObjectPtr<UCharmingCraftInstance> GameInstance = Cast<UCharmingCraftInstance>(GetOuter());
		GameInstance->GetGameEventHandler()->OnBlockPlaceEvent(CachedBuildItemStack, BlockEntityActor, Instigator);
		GetWorld()->GetTimerManager().PauseTimer(InternalTimer);
		BlockEntityActor->EnableBlockCollision();

		TObjectPtr<ADCharacter> Player = Cast<ADCharacter>(Instigator);
		int32 ItemStackSlotIndex = Player->InventoryComponent->FindSlot(CachedBuildItemStack);
		Player->InventoryComponent->RemoveInventoryByItemStack(CachedBuildItemStack, 1);

		CachedBuildItemStack = nullptr;
		BlockEntityActor = nullptr;
		return true;
	}


	return false;
}
