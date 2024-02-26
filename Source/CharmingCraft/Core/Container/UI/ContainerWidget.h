// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/UI/Holder/WidgetHolder.h"
#include "ContainerWidget.generated.h"

class UInventoryComponent;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UContainerWidget : public UWidgetHolder
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UInventoryComponent> ContainInventory;

	virtual void NativeConstruct() override;
};
