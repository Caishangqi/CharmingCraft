// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"
#include "CharmingCraft/Core/Save/Data/RuntimeGameData.h"
#include "Engine/GameInstance.h"
#include "CharmingCraftInstance.generated.h"


class UGamePlayLogicManager;
class UWorldManager;
/**
 * 
 */
class UGameSaveManager;
class UDataTable;

UCLASS()
class CHARMINGCRAFT_API UCharmingCraftInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	UDataTable* ArmorMaterialDataTable;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	UDataTable* MaterialMetaMapper;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	UDataTable* BladeBasicMaterial;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	UDataTable* FullerReinforcedMaterial;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	UDataTable* GuardMakeShiftMaterial;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	UDataTable* HiltBasicMaterial;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Data")
	UDataTable* PommelDecorativeMaterial;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Data")
	TObjectPtr<ADCharacter> PlayerCharacter;

	UCharmingCraftInstance();

	// 获取存档管理器实例
	UFUNCTION(BlueprintCallable, Category = "Save")
	UGameSaveManager* GetSaveManager() const { return SaveManager; }

	// 获取存档管理器实例
	UFUNCTION(BlueprintCallable, Category = "World")
	UWorldManager* GetWorldManager() const { return WorldManager; }

	UFUNCTION(BlueprintCallable, Category = "GamePlayLogic")
	UGamePlayLogicManager* GetGamePlayLogicManager() const { return GamePlayLogicManager; }

	UFUNCTION(BlueprintCallable, Category = "RuntimeGameData")
	URuntimeGameData* GetRuntimeGameData() const { return RuntimeGameData; }

	// 重写GameInstance的初始化方法
	virtual void Init() override;

	virtual void OnStart() override;

public:
	// 存档管理器实例
	UPROPERTY()
	UGameSaveManager* SaveManager;

	UPROPERTY()
	UWorldManager* WorldManager;

	UPROPERTY()
	UGamePlayLogicManager* GamePlayLogicManager;

	UPROPERTY()
	URuntimeGameData* RuntimeGameData;
};
