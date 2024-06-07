// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NativeCraftWorld.generated.h"

/**
 * 
 */

class ACraftWorldWarpPoint;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftWorldPrepare);



UCLASS(Blueprintable, NotBlueprintType)
class CHARMINGCRAFT_API UNativeCraftWorld : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsLoadInMemory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsVisible;
	UPROPERTY(BlueprintAssignable)
	FOnCraftWorldPrepare OnCraftWorldPrepare;

	// The Internal Delegate that used for bind lambda
	DECLARE_MULTICAST_DELEGATE(FOnCraftWorldPrepareInternal);
	FOnCraftWorldPrepareInternal OnCraftWorldPrepareInternal;

	// The blueprint dynamic Delegate that used for bind UObject 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWarpDataUpdate, UNativeCraftWorld *, TargetCraftWorld,ACraftWorldWarpPoint *, TargetCraftWorldWarpPoint);
	UPROPERTY(BlueprintAssignable)
	FOnWarpDataUpdate OnWarpDataUpdate;

private:
	FTimerHandle CraftWorldCheckHandle;
	/*void BroadcastCraftWorldStatus_Internal();*/

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WorldName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> WorldMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULevelStreamingDynamic> GamePlayWorldInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACharacter>> PlayerList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACraftWorldWarpPoint>> LoadedWarpPoints;

public:
	UNativeCraftWorld();
	UFUNCTION(BlueprintCallable)
	bool InitializeWorldInstance();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	FString GetCraftWorldName();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	TArray<ACharacter*> GetCraftWorldPlayers();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	TSoftObjectPtr<UWorld> GetCraftWorldMapRes();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	TArray<ACraftWorldWarpPoint*> GetLoadedWarpPoints();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	ULevelStreamingDynamic* GetGamePlayWorldInstance();

	/*UFUNCTION(BlueprintCallable)
	bool CheckCraftWorldStatus();*/


public:
	// Event
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerJoinWorld(ACharacter* Instigator, UNativeCraftWorld* TargetWorld);
};
