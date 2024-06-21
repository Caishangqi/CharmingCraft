// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/CraftComponent/NativeCraftComponent.h"
#include "UObject/Interface.h"
#include "ComponentizedObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UComponentizedObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHARMINGCRAFT_API IComponentizedObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<UNativeCraftComponent*> GetObjectComponents();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<UNativeCraftComponent*> GetObjectComponentsByClass(TSubclassOf<UNativeCraftComponent> ComponentsClass);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UNativeCraftComponent* AddComponents(UNativeCraftComponent* AddedComponents);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool RemoveComponents(UNativeCraftComponent* RemovededComponents);
};
