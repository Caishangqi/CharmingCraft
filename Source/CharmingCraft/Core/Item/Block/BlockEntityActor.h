// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "BlockEntityActor.generated.h"

UCLASS()
class CHARMINGCRAFT_API ABlockEntityActor : public AInteractObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockEntityActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DisableBlockCollision();
	UFUNCTION(BlueprintCallable)
	void EnableBlockCollision();
};
