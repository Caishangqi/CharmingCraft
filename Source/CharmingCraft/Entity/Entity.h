// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Interface/DAbstractInterObjectPrototype.h"
#include "Entity.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API AEntity : public ADAbstractInterObjectPrototype
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};