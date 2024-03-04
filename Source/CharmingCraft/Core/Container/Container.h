// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInventoryHolder.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "Container.generated.h"

/**
 * TODO: Consider rewrite the Interface and Base Class of Both
 * WorkBench and Container
 */
class UInventoryComponent;

UCLASS()
class CHARMINGCRAFT_API AContainer : public ABlockEntityActor, public IInventoryHolder
{
	GENERATED_BODY()

public:
	/* 属性 */

	/* 方法 */
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	AContainer();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

protected:
	/* 方法 */
};
