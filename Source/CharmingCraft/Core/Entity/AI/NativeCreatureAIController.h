// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "NativeCreatureAIController.generated.h"

UCLASS()
class CHARMINGCRAFT_API ANativeCreatureAIController : public AAIController, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANativeCreatureAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
};
