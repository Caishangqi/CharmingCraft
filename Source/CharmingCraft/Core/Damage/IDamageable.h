// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"
#include "UObject/Interface.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "IDamageable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnActionHit(APawn* InstigatorPawn, FHitData HitData);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UDAttributeComponent* GetAttributeComponent();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleHealthChanged(AActor* InstigatorActor, UDAttributeComponent*
	                         OwningComp, float Health, float HealthDelta);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleDeath();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsDead();
};
