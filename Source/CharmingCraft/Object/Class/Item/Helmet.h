// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Object/Class/Item/Item.h"
#include "Helmet.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UHelmet : public UItem
{
	GENERATED_BODY()

public:
	UHelmet();

	void OnEquipped();
};
