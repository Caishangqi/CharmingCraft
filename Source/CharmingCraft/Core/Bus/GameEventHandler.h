// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "../Core/Save/Data/FSaveSlotInfo.h"
#include "CharmingCraft/Core/Entity/Creature/NativeCreature.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "CharmingCraft/Core/Resource/Gather/ResourceEntityActor.h"
#include "UObject/Object.h"
#include "GameEventHandler.generated.h"

/**
 * Event Bus
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinDelegate, ACharacter*, PlayerCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerOpenInventoryDelegate, ACharacter*, PlayerCharacter, UObject *,
                                             Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerOpenTravelMapDelegate, ACharacter*, PlayerCharacter, UObject *,
                                             Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerOpenContainerDelegate, ACharacter*, Instigator,
                                               UInventoryComponent*, TargetInventory, UObject *, Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOpenWidgetDelegate, UObject*, Instigator, UUserWidget*, TargetWidget);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCloseWidgetDelegate, UObject*, Instigator, UUserWidget*, TargetWidget);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerTravelToRegionDelegate, APawn*, Instigator, UWorld *, TargetWorld)
;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerTravelToSceneDelegate, APawn*, Instigator, UWorld*, FromScene,
                                               UWorld *, TargetScene);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerClickMoveDelegate, ACharacter*, Instigator,
                                             FVector, TargetLocation);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDetailDisplayDelegate, UItemStack*, ItemToDisplay,
                                             UObject *, Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBuildPreviewTraceDelegate, UItemStack *, PreviewItemStack, ACharacter*,
                                             Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlaceModeChangeDelegate, ACharacter*,
                                             Instigator, EBuildMode, ToMode);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBlockBreakDelegate, AActor*, BlockActor, AActor*, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDropDelegate, UItemStack*, DropedItem, UObject*, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnBlockPlaceDelegate, UItemStack*, PreviewItemStack, ABlockEntityActor*,
                                               BlockEntityActor, ACharacter*, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnContainerItemTransferDelegate, UObject*, Instigator,
                                             UInventoryComponent*, SourceContainer, int32, SourceIndex,
                                             UInventoryComponent*, TargetContainer, int32, TargetIndex, UItemStack *,
                                             ItemBeingTransfer);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLeaveDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerSaveDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceEntityBreakDelegate, AActor*, Instigator,
                                             AResourceEntityActor*, TargetResourceEntity);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceEntityPlaceDelegate, UObject*, Instigator,
                                             AResourceEntityActor*, TargetResourceEntity);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerDeathDelegate, UObject*, Instigator, ANativePlayerCharacter*,
                                             TargetPlayer);

// Player
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorOnEquipmentDelegate, UObject *, Instigator, UItemStack *,
                                               OnEquipItem, int32, EquipIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorUnEquipmentDelegate, UObject *, Instigator, UItemStack *,
                                               UnEquipItem, int32, EquipIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemInteractDelegate, APawn*, Instigator, UItemStack*,
                                             InteractItemStack);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerMovementDelegate, APawn*, Instigator, FVector,
                                               FromLocation, FVector, TargetLocation);

// Item Ability System
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnItemDynamicSkillBindDelegate, APawn*, Instigator, UNativeAction*,
                                              FromAction, UNativeAction*,
                                              TargetAction, UItemMeta *, ContextMeta);

// World Management
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUnloadGameLevelComplete, UObject*, Instigator, UWorld *, UnloadedWorld);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoadGameLevelComplete, UObject*, Instigator, UWorld *, LoadedWorld);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUnloadGameLevelStart, UObject*, Instigator, UWorld *, UnloadedWorld);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoadGameLevelStart, UObject*, Instigator, UWorld *, UnloadedWorld);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUnloadWorldChunk, UObject*, Instigator,
                                             ALandChunk*, TargetChunk);

// Craft
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerOpenCraftPannelDelegate, ACharacter*, PlayerCharacter, UObject *,
                                             Creator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCheckRecipeIngredientMatchDelegate, UBaseRecipeEntry *, TargetRecipe,
                                             UInventoryComponent*, TargetContainer);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCraftProcessStartDelegate, UBaseRecipeEntry *, TargetRecipe, int32,
                                              Amount, UInventoryComponent *, Container, UObject *, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnCraftProcessFinishDelegate, UBaseRecipeEntry *, TargetRecipe, int32,
                                              Amount, bool, bIsSuccess, UObject *, Instigator, TArray<UItemStack*>,
                                              RecipeOutPut);

// Creature
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreatureDeadDelegate, UObject*, Instigator, ANativeCreature *,
                                             TargetCreature);

// TODO: 尝试玩家加入世界后，播报事件，让组件接收到这个事件后由组件内部进行调用
UCLASS(BlueprintType)
class CHARMINGCRAFT_API UGameEventHandler : public UObject
{
	GENERATED_BODY()

	UGameEventHandler();

public:
	// World Management
	UPROPERTY(BlueprintAssignable)
	FOnUnloadGameLevelComplete OnUnloadGameLevelComplete;
	UPROPERTY(BlueprintAssignable)
	FOnUnloadGameLevelStart OnUnloadGameLevelStart;
	UPROPERTY(BlueprintAssignable)
	FOnLoadGameLevelStart OnLoadGameLevelStart;
	UPROPERTY(BlueprintAssignable)
	FOnLoadGameLevelComplete OnLoadGameLevelComplete;
	UPROPERTY(BlueprintAssignable)
	FOnUnloadWorldChunk OnUnloadWorldChunk;

	// Global Variable

	// Lowest
	FOnPlayerJoinDelegate OnPlayerJoin;
	FOnPlayerLeaveDelegate OnPlayerLeave;
	FOnPlayerSaveDelegate OnPlayerSave;
	// InGame
	UPROPERTY(BlueprintAssignable)
	FOnPlayerOpenInventoryDelegate OnPlayerOpenInventory;
	UPROPERTY(BlueprintAssignable)
	FOnOpenWidgetDelegate OnOpenWidget;
	UPROPERTY(BlueprintAssignable)
	FOnCloseWidgetDelegate OnCloseWidget;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerOpenContainerDelegate OnPlayerOpenContainer;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerClickMoveDelegate OnPlayerClickMove;
	UPROPERTY(BlueprintAssignable)
	FOnContainerItemTransferDelegate OnContainerItemTransfer;
	UPROPERTY(BlueprintAssignable)
	FOnResourceEntityBreakDelegate OnResourceEntityBreak;
	UPROPERTY(BlueprintAssignable)
	FOnResourceEntityPlaceDelegate OnResourceEntityPlace;
	UPROPERTY(BlueprintAssignable)
	FOnItemDetailDisplayDelegate OnItemDetailDisplay;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerMovementDelegate OnPlayerMovement;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerDeathDelegate OnPlayerDeath;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerOpenTravelMapDelegate OnPlayerOpenTravelMap;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerTravelToRegionDelegate OnPlayerTravelToRegion;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerTravelToSceneDelegate OnPlayerTravelToScene;

	// Craft
	UPROPERTY(BlueprintAssignable)
	FOnPlayerOpenCraftPannelDelegate OnPlayerOpenCraftPannel;
	UPROPERTY(BlueprintAssignable)
	FOnCheckRecipeIngredientMatchDelegate OnCheckRecipeIngredientMatch;
	UPROPERTY(BlueprintAssignable)
	FOnCraftProcessStartDelegate OnCraftProcessStart;
	UPROPERTY(BlueprintAssignable)
	FOnCraftProcessFinishDelegate OnCraftProcessFinish;

	// Player Equipment
	UPROPERTY(BlueprintAssignable)
	FOnActorOnEquipmentDelegate OnActorOnEquipment;
	UPROPERTY(BlueprintAssignable)
	FOnActorUnEquipmentDelegate OnActorUnEquipment;
	UPROPERTY(BlueprintAssignable)
	FOnItemInteractDelegate OnItemInteract;
	// Creature
	UPROPERTY(BlueprintAssignable)
	FOnCreatureDeadDelegate OnCreatureDead;

	// Item Ability System
	UPROPERTY(BlueprintAssignable)
	FOnItemDynamicSkillBindDelegate OnItemDynamicSkillBind;

	// Building System
	UPROPERTY(BlueprintAssignable)
	FOnBuildPreviewTraceDelegate OnBuildPreviewTrace;
	UPROPERTY(BlueprintAssignable)
	FOnBlockPlaceDelegate OnBlockPlace;
	UPROPERTY(BlueprintAssignable)
	FOnBlockBreakDelegate OnBlockBreak;
	UPROPERTY(BlueprintAssignable)
	FOnPlaceModeChangeDelegate OnPlaceModeChange;
	UPROPERTY(BlueprintAssignable)
	FOnItemDropDelegate OnItemDrop;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ANativePlayerCharacter> BlueprintCharacterClassReference;

	// World Management
	UFUNCTION(BlueprintCallable)
	void OnUnloadGameLevelCompleteEvent(UObject* Instigator, UWorld* TargetWorld);
	UFUNCTION(BlueprintCallable)
	void OnUnloadGameLevelStartEvent(UObject* Instigator, UWorld* TargetWorld);
	UFUNCTION(BlueprintCallable)
	void OnLoadGameLevelCompleteEvent(UObject* Instigator, UWorld* TargetWorld);
	UFUNCTION(BlueprintCallable)
	void OnLoadGameLevelStartEvent(UObject* Instigator, UWorld* TargetWorld);
	UFUNCTION(BlueprintCallable)
	void OnPlayerTravelToRegionEvent(APawn* Instigator, UWorld* TargetWorld);
	UFUNCTION(BlueprintCallable)
	void OnPlayerTravelToSceneEvent(APawn* Instigator, UWorld* FromScene, UWorld* TargetScene);

	/*!
	 * Unload the specific Chunk in the world
	 * @param Instigator Who Unload the chunk, it can be WorldManager or Items
	 * @param TargetChunk The Target Chunk
	 */
	UFUNCTION(BlueprintCallable)
	void OnUnloadWorldChunkEvent(UObject* Instigator, ALandChunk* TargetChunk);

	UFUNCTION(BlueprintCallable)
	void OnPlayerJoinEvent();
	UFUNCTION(BlueprintCallable)
	void OnPlayerLeaveEvent();
	UFUNCTION(BlueprintCallable)
	void OnPlayerOpenInventoryEvent(ACharacter* Instigator, UObject* Creator);
	UFUNCTION(BlueprintCallable)
	void OnOpenWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);
	UFUNCTION(BlueprintCallable)
	void OnCloseWidgetEvent(UObject* Instigator, UUserWidget* TargetWidget);
	UFUNCTION(BlueprintCallable)
	void OnPlayerOpenTravelMapEvent(ACharacter* Instigator, UObject* Creator);
	UFUNCTION(BlueprintCallable)
	void OnPlayerOpenContainerEvent(ACharacter* Instigator, UInventoryComponent* TargetContainer, UObject* Creator);
	UFUNCTION(BlueprintCallable)
	void OnPlayerClickMoveEvent(ACharacter* Instigator, FVector TargetLocation);
	UFUNCTION(BlueprintCallable)
	void OnContainerItemTransferEvent(UObject* Instigator, UInventoryComponent* SourceContainer, int32 SourceIndex,
	                                  UInventoryComponent* TargetContainer, int32 TargetIndex,
	                                  UItemStack* ItemBeingTransfer);
	UFUNCTION(BlueprintCallable)
	void OnResourceEntityBreakEvent(AActor* Instigator, AResourceEntityActor* TargetResourceEntity);
	UFUNCTION(BlueprintCallable)
	void OnResourceEntityPlaceEvent(UObject* Instigator, AResourceEntityActor* TargetResourceEntity);
	UFUNCTION(BlueprintCallable)
	void OnPlayerDeathEvent(UObject* Instigator, ANativePlayerCharacter* TargetPlayer);
	// Building
	UFUNCTION(BlueprintCallable)
	void OnBuildPreviewTraceEvent(UItemStack* PreviewItemStack, ACharacter* Instigator);
	UFUNCTION(BlueprintCallable)
	void OnBlockPlaceEvent(UItemStack* PreviewItemStack, ABlockEntityActor* BlockEntityActor, ACharacter* Instigator);
	UFUNCTION(BlueprintCallable)
	void OnBlockBreakEvent(AActor* BlockActor, AActor* Instigator);
	UFUNCTION(BlueprintCallable)
	void OnItemDropEvent(UItemStack* DroppedItem, UObject* Instigator);
	void OnPlaceModeChangeEvent(ACharacter* Instigator, EBuildMode ToMode);

	// Player Equipment
	UFUNCTION(BlueprintCallable)
	void OnActorOnEquipmentEvent(UObject* Instigator, UItemStack* OnEquipItem, int32 EquipIndex);
	UFUNCTION(BlueprintCallable)
	void OnActorUnEquipmentEvent(UObject* Instigator, UItemStack* UnEquipItem, int32 EquipIndex);
	UFUNCTION(BlueprintCallable)
	void OnItemInteractEvent(APawn* Instigator, UItemStack* InteractItemStack);

	// Creature
	UFUNCTION(BlueprintCallable)
	void OnOnCreatureDeadEvent(UObject* Instigator, ANativeCreature* TargetCreature);

	// Player Movement
	UFUNCTION(BlueprintCallable)
	void OnPlayerMovementEvent(APawn* Instigator, FVector FromLocation, FVector TargetLocation);

	UFUNCTION(BlueprintCallable)
	void OnItemDetailDisplayEvent(UItemStack* ItemToDisplay, UObject* Creator);

	// Item Ability System
	UFUNCTION(BlueprintCallable)
	void OnItemDynamicSkillBindEvent(APawn* Instigator, UNativeAction* FromAction, UNativeAction* TargetAction,
	                                 UItemMeta* ContextMeta);

	// Craft
	UFUNCTION(BlueprintCallable)
	void OnPlayerOpenCraftPannelEvent(ACharacter* Instigator, UObject* Creator);
	UFUNCTION(BlueprintCallable)
	void OnCheckRecipeIngredientMatchEvent(UBaseRecipeEntry* TargetRecipe, UInventoryComponent* TargetContainer);
	UFUNCTION(BlueprintCallable)
	void OnCraftProcessStartEvent(UBaseRecipeEntry* TargetRecipe, int32 Amount, UInventoryComponent* Container,
	                              UObject* Instigator);
	UFUNCTION(BlueprintCallable)
	void OnCraftProcessFinishEnvent(UBaseRecipeEntry* TargetRecipe, int32 Amount, bool bIsSuccess, UObject* Instigator,
	                                TArray<UItemStack*> RecipeOutPut);
};
