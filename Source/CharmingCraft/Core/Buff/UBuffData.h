// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuffModel.h"
#include "Enum/EBuffRemoveStackUpdate.h"
#include "Enum/EBuffTimeUpdate.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "UBuffData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API UBuffData : public UObject
{
	GENERATED_BODY()

public: // Basic Information
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName BuffName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Priority;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxStack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer Tags;

public: // Internal Value
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, int32> InternalValue;

public: // Temporal Information
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsForever;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TickTime;

public: // Update Methods
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBuffTimeUpdate BuffTimeUpdate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBuffRemoveStackUpdate BuffRemoveStackUpdate;

public: // CallBack
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseBuffModel> OnCreate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseBuffModel> OnRemove;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseBuffModel> OnTick;

	// Damage Callback
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseBuffModel> OnHit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseBuffModel> OnBeHit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseBuffModel> OnKill;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UBaseBuffModel> OnBeKill;
};
