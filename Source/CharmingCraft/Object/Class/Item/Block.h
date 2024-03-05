// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "Block.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBlock : public UItem
{
	GENERATED_BODY()

public:
	UBlock();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block")
	TSubclassOf<ABlockEntityActor> DefaultBlockEntityActorClass;

	
};
