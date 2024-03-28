// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeItemAction.h"
#include "NativeEquipmentAction.generated.h"

/**
 * 
 */
class AEquipmentEntityActor;

UCLASS()
class CHARMINGCRAFT_API UNativeEquipmentAction : public UNativeItemAction
{
	GENERATED_BODY()

public:
	// The Item "Model" that handle trace logic and collision
	// The Item Animation temporary store in 
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AEquipmentEntityActor> ItemEntityActor;

public:
	UNativeEquipmentAction();

	virtual void StartAction_Implementation(APawn* Instigator) override;
};
