// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Interface/ActionOnHitInterface.h"
#include "CharmingCraft/Interface/DAbstractInterObjectPrototype.h"
#include "Entity.generated.h"

class UDamageIndicator;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API AEntity : public ADAbstractInterObjectPrototype, public IActionOnHitInterface
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
	virtual void OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData) override;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//UDamageIndicator* DamageIndicator;
};
