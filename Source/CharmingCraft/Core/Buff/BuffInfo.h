// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UBuffData.h"
#include "UObject/Object.h"
#include "BuffInfo.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuffInfoRemoved, UBuffInfo*, RemovedBuffInfo);

UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API UBuffInfo : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBuffData> BuffData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APawn> Instigator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APawn> Target;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TickTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentStack = 1;

	UPROPERTY(BlueprintAssignable)
	FOnBuffInfoRemoved OnBuffInfoRemoved;
};
