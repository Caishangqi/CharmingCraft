// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Object/Components/DInventoryComponent.h"
#include "WorkBenchComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UWorkBenchComponent : public UDInventoryComponent
{
	GENERATED_BODY()

protected:
	/* 属性 */

public:
	UWorkBenchComponent();
};
