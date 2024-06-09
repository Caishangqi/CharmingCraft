// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "UObject/Object.h"
#include "Templates/Function.h"
#include "WorldManager.generated.h"

class UNativeCraftWorld;
class AWorldEntityManager;
class ULevelStreamingDynamic;

USTRUCT(BlueprintType)
struct FCharmingCraftWorld
{
	GENERATED_BODY()

public:
	FCharmingCraftWorld(): IsSuccess(false), GamePlayWorld(nullptr)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> WorldTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULevelStreamingDynamic> GamePlayWorld;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACharacter>> PlayerList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WorldName;
};

/**
 * 
 */
// 在游戏模式头文件中
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoadedDelegate);

UCLASS()
class CHARMINGCRAFT_API UWorldManager : public UObject, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TObjectPtr<UNativeCraftWorld>> Worlds;

	/*!
	 * Get Player Current CraftWorld instance player joined, this world
	 * is exactly the player current joined and the world's player list
	 * should have the target player.
	 * @param PlayerCharacter 
	 * @return PlayerCurrent CraftWorlds instance
	 */
	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* GetPlayerCurrentWorld(ACharacter* PlayerCharacter);
	/*!
	 * Get Player Current Region, this is different with GetPlayerCurrentWorld, player current
	 * world could be any world but region world can not be scene and dungeon "instance" world
	 * @param PlayerCharacter 
	 * @return PlayerCurrentRegion CraftWorlds
	 */
	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* GetPlayerCurrentRegion(ACharacter* PlayerCharacter);

	UNativeCraftWorld* TeleportPlayerToWorld_Internal(ACharacter* PlayerCharacter, FString WorldName,
	                                                  UNativeCraftWorld* TargetWorld = nullptr);
	
	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* GetWorldByWorldName(FString SearchWorldName);

	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* LoadCraftWorldInMemory(TSubclassOf<UNativeCraftWorld> TargetWorld);
	/*!
	 *	Get the CraftWorld that currently display to player
	 *	Note: Only 1 World could display ! The method would
	 *	automatically Hidden other worlds and brodcast player
	 *	left world event
	 */
	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* GetShownWorld();

	UFUNCTION(BlueprintCallable)
	bool UnLoadCraftWorldInMemory(UNativeCraftWorld* TargetWorld);

	/*!
	 * Shown CraftWorld to player, the function will automatically Hidden
	 * all CraftWorld that is not {TargetWorld}
	 * @param TargetWorld The target CraftWorld need to be shown to player
	 * @return TargetWorld
	 */
	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* ShownCraftWorld(UNativeCraftWorld* TargetWorld);

	UFUNCTION(BlueprintCallable)
	UNativeCraftWorld* HiddenCraftWorld(UNativeCraftWorld* TargetWorld);


	UFUNCTION(BlueprintCallable)
	bool TeleportPlayerToWarp(APawn* PlayerCharacter, const FName WarpPoint);

	/*!
	 * This is a more official or logic way to bind runtime generated actor to a
	 * specific level instance, be sure you put a WorldEntityManager in your world
	 * or else it will return null pointer
	 *
	 * Also be sure to load only ONE WorldEntityManager in the world or it will cause
	 * problem
	 *
	 * Alternatively if you don't want to put AWorldEntityManager in the level manually
	 * you can use GetPlayerCurrentLevel and get level instance related script actor
	 * although it is wierd @see GetPlayerCurrentLevel()
	 * @return AWorldEntityManager related to current level
	 */
	UFUNCTION(BlueprintCallable)
	AWorldEntityManager* GetWorldEntityManager();

	/*!
	 * Teleport player to specific Warp of ACraftWorldWarpPoint
	 * please check the level is loaded and visible before teleport
	 * @param PlayerCharacter 
	 * @param WarpPoint 
	 * @return whether or not teleport successful
	 */
	UFUNCTION(BlueprintCallable)
	bool TravelPlayerToWarp(APawn* PlayerCharacter, const FName WarpPoint);

public:
	// Interface
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
};
