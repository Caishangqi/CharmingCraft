// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/Item/Meta/ItemMeta.h"
#include "IntegratedMeta.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UIntegratedMeta : public UItemMeta
{
	GENERATED_BODY()

public:
	UIntegratedMeta();

	// Layout for UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Layout")
	TSubclassOf<UUserWidget> Layout;
};
