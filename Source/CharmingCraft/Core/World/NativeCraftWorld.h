// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Camera/CameraManager.h"
#include "UObject/Object.h"
#include "NativeCraftWorld.generated.h"
/**
 * 
 */
class ACraftWarpPoint;


UCLASS(Blueprintable, NotBlueprintType)
class CHARMINGCRAFT_API UNativeCraftWorld : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsLoadInMemory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FString> CraftWorldMetaData;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftWorldPrepare);

	UPROPERTY(BlueprintAssignable)
	FOnCraftWorldPrepare OnCraftWorldPrepare;

	// The Internal Delegate that used for bind lambda
	DECLARE_MULTICAST_DELEGATE(FOnCraftWorldPrepareInternal);
	FOnCraftWorldPrepareInternal OnCraftWorldPrepareInternal;

	// The blueprint dynamic Delegate that used for bind UObject 
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWarpDataUpdate, UNativeCraftWorld *, TargetCraftWorld,
	                                             ACraftWarpPoint *, TargetCraftWorldWarpPoint);

	UPROPERTY(BlueprintAssignable)
	FOnWarpDataUpdate OnWarpDataUpdate;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWarpDataUpdateInternal, UNativeCraftWorld *, ACraftWarpPoint *);
	FOnWarpDataUpdateInternal OnWarpDataUpdateInternal;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WorldName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> WorldMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULevelStreamingDynamic> GamePlayWorldInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<ACharacter*> PlayerList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSuccess = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSet<ACraftWarpPoint*> LoadedWarpPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECameraPerspectiveEnum TargetCameraPerspective = ECameraPerspectiveEnum::INCLINE;
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNativeCraftWorld> AssociateCraftWorld;

public:
	UNativeCraftWorld();
	UFUNCTION(BlueprintCallable)
	bool InitializeWorldInstance();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	FString GetCraftWorldName();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	TSet<ACharacter*> GetCraftWorldPlayers();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	TSoftObjectPtr<UWorld> GetCraftWorldMapRes();
	UFUNCTION(BlueprintCallable, BlueprintGetter)
	TSet<ACraftWarpPoint*> GetLoadedWarpPoints();

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	ULevelStreamingDynamic* GetGamePlayWorldInstance();
	UFUNCTION(BlueprintCallable, BlueprintGetter)
	ECameraPerspectiveEnum GetTargetCameraPerspective();

	UFUNCTION(BlueprintCallable)
	TSet<ACharacter*> AddPlayerToWorldPlayerList(ACharacter* Player);

	UFUNCTION(BlueprintCallable)
	TSet<ACharacter*> RemovePlayerFromWorldPlayerList(ACharacter* Player);

public:
	// Event
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerJoinWorld(ACharacter* Instigator, UNativeCraftWorld* TargetWorld);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlayerLeftWorld(ACharacter* Instigator, UNativeCraftWorld* TargetWorld);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCraftWorldHidden(UNativeCraftWorld* TargetWorld);

private:
	TSet<ACharacter*> PendingRemovePlayerList;
};
