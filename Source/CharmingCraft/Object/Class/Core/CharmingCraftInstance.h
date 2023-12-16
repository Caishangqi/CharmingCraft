// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCharacter.h"

#include "Engine/GameInstance.h"
#include "CharmingCraftInstance.generated.h"


/**
 * 
 */
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
};
