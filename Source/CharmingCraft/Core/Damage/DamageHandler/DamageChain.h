// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageHandler.h"
#include "EDamageHandlerType.h"
#include "UObject/Object.h"
#include "DamageChain.generated.h"


/**
 * Damage Chain Control the order of damage handle
 * The Class should inside the Attribute Component
 * and should initialize at BeginPlay()
 */
UCLASS(BlueprintType)
class CHARMINGCRAFT_API UDamageChain : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UDamageHandler> FirstHandler;

	UPROPERTY()
	TObjectPtr<UDAttributeComponent> AttributeComponent;

	/*!
	 * Initialize the DamageChain, user should pass in AttributeComponent
	 * For the developer, you need decided the order of chain inside this
	 * method
	 * @return it self
	 */
	UDamageChain* InitializeChain();

	/*!
	 * Handle the HitData received by its instigator
	 * @param HitData The inward HitData
	 */
	UFUNCTION(BlueprintCallable)
	void HandleDamage(FHitData HitData);

protected:
	static const TObjectPtr<UDamageHandler> CreateDamageHandler(EDamageHandlerType HandlerType, UObject* Outer);
	
};
