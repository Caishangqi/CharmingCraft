// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/DAbstractInterObjectPrototype.h"
#include "DropItem.generated.h"

class UItemStack;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADropItem : public ADAbstractInterObjectPrototype
{
	GENERATED_BODY()

public:
	ADropItem();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Drop Item Properties")
	UItemStack* ItemStack;
};
