// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FSaveSlotInfo.h"
#include "Render/PlayerMeshRenderActor.h"
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
	TObjectPtr<APlayerMeshRenderActor> CharacterDisplayMiddle;

	/* Display */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APlayerMeshRenderActor> CharacterDisplayRight;

	/* Display */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APlayerMeshRenderActor> CharacterDisplayLeft;

	// 存储有效存档的信息
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<FSaveSlotInfo> ValidSaveSlots;

	// 创建一个存储整型的双向链表
	TDoubleLinkedList<FSaveSlotInfo> ValidSaveSlotsRing;

	// A Cached Slot for Create FSaveSlotInfo in BP UMG
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FSaveSlotInfo CachedLoadSlots;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FSaveSlotInfo PrepareSaveSlot;

public:
	UFUNCTION(BlueprintCallable)
	// Helper function to actually perform the save operation
	bool PerformSaveGameToFile(const FSaveSlotInfo& SaveSlotName);
	UFUNCTION(BlueprintCallable)
	// Helper function to actually perform the save operation
	bool PerformSaveGamesToFile();
	UFUNCTION(BlueprintCallable)
	// Helper function to actually perform the load operation
	void PerformLoadGamesFromFile();
	// Save Game Information to current select GameSlot and PerformSaveGameToFile()
	UFUNCTION(BlueprintCallable)
	bool SaveGameToGameSlot();
	// Load single SaveSlot and add to the ValidSaveSlotsRing
	UFUNCTION(BlueprintCallable)
	bool CreateNewSlotAndSave(FSaveSlotInfo SaveSlotName);
	UFUNCTION(BlueprintCallable)
	void PerformLoadGameFromFile(FSaveSlotInfo& SaveSlotName);

	/* The Pointer that Point to the current select, In graphic: it is in center */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FSaveSlotInfo CurrentSaveNode;

	UFUNCTION(BlueprintCallable)
	FSaveSlotInfo& GetCurrentSaveSlot();
	// Should call on Initialize the UMG
	UFUNCTION(BlueprintCallable)
	bool SetCurrentSlot();
	UFUNCTION(BlueprintCallable)
	bool SetPreviewSlotAsCurrentSlot();
	UFUNCTION(BlueprintCallable)
	FSaveSlotInfo& GetPreviewSlot();
	UFUNCTION(BlueprintCallable)
	bool SetNextSlotAsCurrentSlot();
	UFUNCTION(BlueprintCallable)
	FSaveSlotInfo& GetNextSlot();
	UFUNCTION(BlueprintCallable)
	int32 GetValidSaveSlotsRingNumber();

	UFUNCTION(BlueprintCallable)
	bool DeleteCurrentSaveSlot();

	UFUNCTION(BlueprintCallable)
	void SetSelectStateForSlot();
	bool RefreshSaveSlotRing();

	/* Render Manipulation */
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerMeshRenderActorInfo();
};
