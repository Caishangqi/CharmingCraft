// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "../Core/Interact/NativeInteractActor.h"
#include "Entity.generated.h"

class UDamageIndicator;
class UDAttributeComponent;

UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API AEntity : public ANativeInteractActor, public IDamageable
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

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="默认")
	TObjectPtr<UDAttributeComponent> AttributeComponent;


	/** TODO: Need to investigate why the component is inactive */
	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="默认")
	// TObjectPtr<UDamageIndicator> DamageIndicator;
};
