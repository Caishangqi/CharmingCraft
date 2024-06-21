// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/CraftComponent/NativeCraftComponent.h"
#include "ItemSKillComponent.generated.h"

class UNativeAction;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UItemSKillComponent : public UNativeCraftComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UNativeAction> ActionInstance;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UNativeAction> ActionTemplateClass;
};
