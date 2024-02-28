// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "CharmingCraft/Core/Container/Enum/EEquipmentSocket.h"
#include "Equipment.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UEquipment : public UItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Socket")
	EEquipmentSocket Socket;
};
