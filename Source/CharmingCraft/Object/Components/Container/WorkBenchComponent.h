// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/Container/Inventory/InventoryComponent.h"
#include "CharmingCraft/Core/Container/UI/PlayerInventoryWidget.h"

#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "WorkBenchComponent.generated.h"

class UEquipPartComponent;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UWorkBenchComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:
	/* 属性 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Layout")
	UUserWidget* SavedLayout;

	/* 属性 */

public:
	UWorkBenchComponent();

	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

	UFUNCTION(BlueprintCallable)
	bool SetPartMaterial(UEquipPartComponent* Component, EMaterial Material);
};
