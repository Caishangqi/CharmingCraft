// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "Data/FSaveSlotInfo.h"
#include "UObject/Object.h"
#include "GameSaveManager.generated.h"


/**
 * GameSaveManager Class
 * This class manages game save and load operations.
 */
class USaveGame;

UCLASS()
class CHARMINGCRAFT_API UGameSaveManager : public UObject
{
	GENERATED_BODY()
	// 定义一个用于存储有效存档信息的结构

public:
	UGameSaveManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ACameraActor> NormalCamera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ACameraActor> CloseCamera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ACameraActor> FarCamera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ACameraActor> Detailed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Costume")
	UDataTable* InternalCostume;

	// Save current game state to a file
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool SaveGameToFile(const FString& SaveSlotName);

	// Load game state from a file
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool LoadGameFromFile(const FString& SaveSlotName);

	// Check if a save file exists
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool DoesSaveGameExist(const FString& SaveSlotName);

	UFUNCTION(BlueprintCallable, Category = "Save")
	void UpdateSaveSlots();

	/* Display */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ASkeletalMeshActor> CharacterDisplayMain;

	/* Display */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ASkeletalMeshActor> CharacterDisplaySecond;

	/* Display */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<ASkeletalMeshActor> CharacterDisplayThird;

	// 存储有效存档的信息
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<FSaveSlotInfo> ValidSaveSlots;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FSaveSlotInfo CachedLoadSlots;

public:
	// Initialize a new save game
	void InitializeNewSaveGame();

	UFUNCTION(BlueprintCallable)
	// Helper function to actually perform the save operation
	bool PerformSaveGameToFile(const FSaveSlotInfo& SaveSlotName);
	UFUNCTION(BlueprintCallable)
	// Helper function to actually perform the load operation
	void PerformLoadGameFromFile();
};
