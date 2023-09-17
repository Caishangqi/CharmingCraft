// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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

	UCharmingCraftInstance();
};
