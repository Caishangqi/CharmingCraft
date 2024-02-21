// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContainerWidget.h"
#include "PlayerInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerInventoryWidget : public UContainerWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
};
