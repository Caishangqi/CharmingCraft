// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemMeta.h"
#include "BlockMeta.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBlockMeta : public UItemMeta
{
	GENERATED_BODY()
public:
	UBlockMeta();
	virtual AItemEntityActor* CreateItemEntityActor(const UObject* WorldContextObject) override;
};
