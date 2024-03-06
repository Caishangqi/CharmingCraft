// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerModeBase.h"
#include "PlayerModeBuild.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerModeBuild : public UPlayerModeBase
{
	GENERATED_BODY()
public:
	UPlayerModeBuild();
	virtual void UpdateControllerMappingContext(EPlayerMode FromGameMode, ACharacter* Instigator, EPlayerMode NewPlayerMode) override;
};
