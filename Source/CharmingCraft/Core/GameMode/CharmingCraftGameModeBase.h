// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CharmingCraftGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ACharmingCraftGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACharmingCraftGameModeBase();
public:

	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	
};
