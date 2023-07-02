// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DAction.generated.h"

/**
 * 
 */

class UWorld;
/*
 *	Because we drive the Class from UObject, without UCLASS(Blueprintable), we can
 *	not make child classes from as Action
 */

UCLASS(Blueprintable)
class CHARMINGCRAFT_API UDAction : public UObject
{
	GENERATED_BODY()

public:
	/* Action nickname to start/stop without a reference to the object */
	UPROPERTY(EditDefaultsOnly, Category= "Action")
	FName ActionName; // FName is hashed used in game, highly optimized

	/*
	 *	BlueprintNativeEvent it means that it has a native implementation which is C++,
	 *	so we can implement it in cpp, also it allows blueprints to overwrite it.
	 *
	 *	Also, because we mark this BlueprintNativeEvent, the implementation will be
	 *	_Implementation
	 */
	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	void StartAction(AActor* Instigator); // Passing who is responsible for starting the action


	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	void StopAction(AActor* Instigator);

	virtual UWorld* GetWorld() const override;
};
