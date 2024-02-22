// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContainerWidget.h"
#include "CharmingCraft/Core/UI/ICommonUI.h"
#include "PlayerInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerInventoryWidget : public UContainerWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
