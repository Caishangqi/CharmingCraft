// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NativeCCGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ANativeCCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANativeCCGameModeBase();

public:
	
	virtual void BeginPlay() override;
};
