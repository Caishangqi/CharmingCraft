// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEventHandler.h"

#include "EngineUtils.h"
#include "../Core/Save/GameSaveManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "GameFramework/PlayerStart.h"
#include "../Core/Save/Lib/CharacterSaveLib.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Resource/Chunk/LandChunk.h"

UGameEventHandler::UGameEventHandler()
{
	static ConstructorHelpers::FClassFinder<ADCharacter> BlueprintClass(
		TEXT("/Game/CharmingCraft/PlayerCharacter.PlayerCharacter"));

	if (BlueprintClass.Class != nullptr)
	{
		BlueprintCharacterClassReference = BlueprintClass.Class;
	}
	//FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject()
}

void UGameEventHandler::OnUnloadGameLevelEvent(UWorld* TargetWorld)
{
	OnUnloadGameLevel.Broadcast(TargetWorld);
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Event trigger at UGameEventHandler::OnUnloadGameLevelEvent()\n"
		       "		TargetWorld: %s"), *TargetWorld->GetMapName());
}

void UGameEventHandler::OnUnloadWorldChunkEvent(UObject* Instigator, UWorld* TargetWorld, ALandChunk* TargetChunk)
{
	OnUnloadWorldChunk.Broadcast(Instigator, TargetWorld, TargetChunk);
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Event trigger at UGameEventHandler::OnUnloadWorldChunkEvent()\n"
		       "		TargetWorld:	%s\n"
		       "		TargetChunk:	%s\n"
		       "		Instigator:		%s")
	       , *TargetWorld->GetName(), *TargetChunk->GetName(), *Instigator->GetName());
}

void UGameEventHandler::OnPlayerJoinEvent()
{
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Event trigger at UGameEventHandler::OnPlayerJoinBegin()"));

	APlayerStart* DesiredPlayerStart = nullptr;

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if (PlayerStart && PlayerStart->IsA(APlayerStart::StaticClass()))
		{
			// 可以添加更多的条件判断，来选择特定的PlayerStart
			DesiredPlayerStart = PlayerStart;
			break; // 如果您只有一个PlayerStart或者不需要特定的条件，找到一个后即可停止循环
		}
	}

	TObjectPtr<UCharmingCraftInstance> CharmingCraftInstance = Cast<UCharmingCraftInstance>(GetOuter());
	UPlayerData* PlayerData = CharmingCraftInstance->GetSaveManager()->GetCurrentSaveSlot().PlayerData;
	TObjectPtr<ADCharacter> InGamePlayerCharacter = Cast<ADCharacter>(
		CharmingCraftInstance->GetRuntimeGameData()->PlayerCharacter);
	// Set Player Hidden First
	CharmingCraftInstance->GetRuntimeGameData()->PlayerCharacter->SetActorHiddenInGame(true);


	TObjectPtr<UMaterial> PlayerSkin = UCharacterSaveLib::FindPreviewMaterialFromCostumeId(
		CharmingCraftInstance->GetSaveManager()->InternalCostume,
		PlayerData->PlayerInfo.CostumeId);

	UCharacterSaveLib::ApplyCostumeToPlayer(
		InGamePlayerCharacter, PlayerSkin);

	// Handle Player Location
	if (!PlayerData->PlayerLocation.bIsSpawnPoint)
	{
		InGamePlayerCharacter->TeleportTo(
			PlayerData->PlayerLocation.PlayerLocation,
			PlayerData->PlayerLocation.PlayerRotation);
		PlayerData->PlayerLocation.bIsSpawnPoint = false;
	}
	else
	{
		PlayerData->PlayerLocation.bIsSpawnPoint = false;
	}

	// BoardCast Global Event
	OnPlayerJoin.Broadcast(InGamePlayerCharacter);

	// Set Player Visible After Load Location
	CharmingCraftInstance->GetRuntimeGameData()->PlayerCharacter->SetActorHiddenInGame(false);
}

void UGameEventHandler::OnPlayerLeaveEvent()
{
	OnPlayerSave.Broadcast();
}

void UGameEventHandler::OnPlayerOpenInventoryEvent(ACharacter* Instigator, UObject* Creator)
{
	OnPlayerOpenInventory.Broadcast(Instigator, Creator);
}

void UGameEventHandler::OnPlayerOpenContainerEvent(ACharacter* Instigator, UInventoryComponent* TargetContainer,
                                                   UObject* Creator)
{
	OnPlayerOpenContainer.Broadcast(Instigator, TargetContainer, Creator);
}

void UGameEventHandler::OnPlayerClickMoveEvent(ACharacter* Instigator, FVector TargetLocation)
{
	OnPlayerClickMove.Broadcast(Instigator, TargetLocation);
}

void UGameEventHandler::OnContainerItemTransferEvent(UObject* Instigator, UInventoryComponent* SourceContainer,
                                                     int32 SourceIndex, UInventoryComponent* TargetContainer,
                                                     int32 TargetIndex, UItemStack* ItemBeingTransfer)
{
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Event trigger at UGameEventHandler::OnContainerItemTransferEvent()"));
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT(
		       "		 [I] Instigator =			%s							owner = %s\n"
		       "		 [S] SourceContainer =		%s			index = %d		owner = %s\n"
		       "		 [T] TargetContainer =		%s			index = %d		owner = %s\n"
		       "		 [C] ItemBeingTransfer =	%s"
	       ),
	       *Instigator->GetName(), *Cast<UActorComponent>(Instigator)->GetOwner()->GetName(),
	       *SourceContainer->GetName(), SourceIndex, * SourceContainer->GetOwner()->GetName(),
	       *TargetContainer->GetName(), TargetIndex, * TargetContainer->GetOwner()->GetName(),
	       *ItemBeingTransfer->ItemMeta->DisplayName
	);
	OnContainerItemTransfer.Broadcast(Instigator, SourceContainer, SourceIndex, TargetContainer, TargetIndex,
	                                  ItemBeingTransfer);
}

void UGameEventHandler::OnResourceEntityBreakEvent(AActor* Instigator, AResourceEntityActor* TargetResourceEntity)
{
	OnResourceEntityBreak.Broadcast(Instigator, TargetResourceEntity);
	UE_LOG(LogChamingCraftResource, Display,
	       TEXT("[⛏️]  Resource Entity Actor Has been Destroy"));
	UE_LOG(LogChamingCraftResource, Display,
	       TEXT(
		       "		 [I] Instigator =		%s\n"
		       "		 [T] Target Resource Actor =		%s"
	       ),
	       *Instigator->GetName(), *TargetResourceEntity->GetName());
}

void UGameEventHandler::OnResourceEntityPlaceEvent(UObject* Instigator, AResourceEntityActor* TargetResourceEntity)
{
	OnResourceEntityPlace.Broadcast(Instigator, TargetResourceEntity);
}

void UGameEventHandler::OnBuildPreviewTraceEvent(UItemStack* PreviewItemStack, ACharacter* Instigator)
{
	OnBuildPreviewTrace.Broadcast(PreviewItemStack, Instigator);
	UE_LOG(LogChamingCraftBuild, Display,
	       TEXT("[📦]  BuildModuleManager start build trace\n"
		       "		 [I] Cached ItemStack =			%s\n"
		       "		 [I] Instigator =				%s"), *PreviewItemStack->ItemMeta->DisplayName, *Instigator->GetName());
}

void UGameEventHandler::OnBlockPlaceEvent(UItemStack* PreviewItemStack, ABlockEntityActor* BlockEntityActor,
                                          ACharacter* Instigator)
{
	OnBlockPlace.Broadcast(PreviewItemStack, BlockEntityActor, Instigator);
	UE_LOG(LogChamingCraftBuild, Display,
	       TEXT("[📦]  BuildModuleManager place a block\n"
		       "		 [I] Cached ItemStack =			%s\n"
		       "		 [I] Instigator =				%s\n"
		       "		 [B] BlockEntityActor =				%s"), *PreviewItemStack->ItemMeta->DisplayName, *Instigator->GetName(),
	       *BlockEntityActor->GetName());
}

void UGameEventHandler::OnBlockBreakEvent(AActor* BlockActor, AActor* Instigator)
{
	OnBlockBreak.Broadcast(BlockActor, Instigator);
}

void UGameEventHandler::OnItemDropEvent(UItemStack* DroppedItem, UObject* Instigator)
{
	OnItemDrop.Broadcast(DroppedItem, Instigator);
}

void UGameEventHandler::OnPlaceModeChangeEvent(ACharacter* Instigator, EBuildMode ToMode)
{
	OnPlaceModeChange.Broadcast(Instigator, ToMode);
}

void UGameEventHandler::OnActorOnEquipmentEvent(UObject* Instigator, UItemStack* OnEquipItem, int32 EquipIndex)
{
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Event trigger at UGameEventHandler::OnActorOnEquipmentEvent()"));
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT(
		       "		 [I] Instigator =			%s									  \n"
		       "		 [E] OnEquipItem =			%s									  \n"
		       "		 [E] EquipIndex =		    %d									  \n"

	       ),
	       *Instigator->GetName(),
	       *OnEquipItem->ItemMeta->DisplayName,
	       EquipIndex
	);
	OnActorOnEquipment.Broadcast(Instigator, OnEquipItem, EquipIndex);
}

void UGameEventHandler::OnActorUnEquipmentEvent(UObject* Instigator, UItemStack* UnEquipItem, int32 EquipIndex)
{
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT("[📍]  Event trigger at UGameEventHandler::OnActorUnEquipmentEvent()"));
	UE_LOG(LogChamingCraftGameEvent, Display,
	       TEXT(
		       "		 [I] Instigator =			%s									  \n"
		       "		 [U] UnEquipItem =			%s									  \n"
		       "		 [E] EquipIndex =			%d									  \n"

	       ),
	       *Instigator->GetName(),
	       *UnEquipItem->ItemMeta->DisplayName,
	       EquipIndex
	);
	OnActorUnEquipment.Broadcast(Instigator, UnEquipItem, EquipIndex);
}

void UGameEventHandler::OnItemInteractEvent(APawn* Instigator, UItemStack* InteractItemStack)
{
	OnItemInteract.Broadcast(Instigator, InteractItemStack);
}

void UGameEventHandler::OnPlayerMovementEvent(APawn* Instigator, FVector FromLocation, FVector TargetLocation)
{
	OnPlayerMovement.Broadcast(Instigator, FromLocation, TargetLocation);
}

void UGameEventHandler::OnItemDetailDisplayEvent(UItemStack* ItemToDisplay, UObject* Creator)
{
	OnItemDetailDisplay.Broadcast(ItemToDisplay, Creator);
}

void UGameEventHandler::OnCloseWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget)
{
	OnCloseWidget.Broadcast(Instigator, TargetWidget);
}

void UGameEventHandler::OnItemDynamicSkillBindEvent(APawn* Instigator, UDAction* FromAction, UDAction* TargetAction,
                                                    UItemMeta* ContextMeta)
{
	OnItemDynamicSkillBind.Broadcast(Instigator, FromAction, TargetAction, ContextMeta);
}
