// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPlayerMode.h"
#include "UObject/Object.h"
#include "PlayerModeManager.generated.h"

class ADCharacter;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerModeChangeDelegate, ACharacter *, Instigator, EPlayerMode,
                                             ToMode);

UCLASS()
class CHARMINGCRAFT_API UPlayerModeManager : public UObject
{
	GENERATED_BODY()

public:
	UPlayerModeManager();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EPlayerMode CurrentPlayerMode;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FOnPlayerModeChangeDelegate OnPlayerModeChangeDelegate;

	UFUNCTION(BlueprintCallable)
	void ChangePlayerMode(ACharacter* Instigator, EPlayerMode NewPlayerMode);
};
