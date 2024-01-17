// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInventoryHolder.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "Container.generated.h"

/**
 * TODO: Consider rewrite the Interface and Base Class of Both
 * WorkBench and Container
 */
class UDInventoryComponent;

UCLASS()
class CHARMINGCRAFT_API AContainer : public AInteractObject, public IInventoryHolder
{
	GENERATED_BODY()

public:
	/* 属性 */

	/* 方法 */
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	AContainer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<UDInventoryComponent> InventoryComponent;

protected:
	/* 方法 */
};