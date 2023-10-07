// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActorGenerator.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UActorGenerator : public UObject
{
	GENERATED_BODY()

public:
	static UActorGenerator* Get();

	template <class T>
	T* Generate(T Class);

private:
	static UActorGenerator* Instance;
};
