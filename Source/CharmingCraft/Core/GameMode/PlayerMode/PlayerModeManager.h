// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/GameMode/Enum/EPlayerMode.h"
#include "Mode/PlayerModeBase.h"
#include "UObject/Object.h"
#include "PlayerModeManager.generated.h"

class ADCharacter;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerModeChangeDelegate, EPlayerMode, FromGameMode, ACharacter *,
                                               Instigator, EPlayerMode,
                                               ToMode);

UCLASS()
class CHARMINGCRAFT_API UPlayerModeManager : public UObject
{
	GENERATED_BODY()

public:
	UPlayerModeManager();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UPlayerModeBase> CurrentPlayerMode;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, BlueprintAssignable)
	FOnPlayerModeChangeDelegate OnPlayerModeChangeDelegate;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<EPlayerMode, TObjectPtr<UPlayerModeBase>> LoadedPlayerMods;

	UFUNCTION(BlueprintCallable)
	void ChangePlayerMode(EPlayerMode FromGameMode, ACharacter* Instigator, EPlayerMode NewPlayerMode);
};
