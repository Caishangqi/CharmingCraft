// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NativeCraftWorld.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, NotBlueprintType)
class CHARMINGCRAFT_API UNativeCraftWorld : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsLoadInMemory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsVisible;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLevelStreamingLoadedStatus OnLevelLoaded;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLevelStreamingVisibilityStatus OnLevelHidden;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLevelStreamingVisibilityStatus OnLevelShown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FLevelStreamingLoadedStatus OnLevelUnloaded;

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
	ULevelStreamingDynamic* GetGamePlayWorldInstance();
};
