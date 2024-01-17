// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Container/Container.h"
#include "ProcessUnit.generated.h"

UCLASS()
class CHARMINGCRAFT_API AProcessUnit : public AContainer
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProcessUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
