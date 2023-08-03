// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DPlayerAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADPlayerAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	// 缓存目标Actor
	TWeakObjectPtr<AActor> TargetActor;
};
