// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "Data/NativeDungeonInstance.h"
#include "UObject/Object.h"
#include "NativeDungeonHandler.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UNativeDungeonHandler : public UObject, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TObjectPtr<UNativeDungeonInstance>> LoadedDungeonInstances;

public:
	UNativeDungeonHandler();

public:
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
};
