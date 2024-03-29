// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeItemAction.h"
#include "NativeOnHitAction.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UNativeOnHitAction : public UNativeItemAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<AActor> TargetActor;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FHitData AppliedHitData;
public:

};
