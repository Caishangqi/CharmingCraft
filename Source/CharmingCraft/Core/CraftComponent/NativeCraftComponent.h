// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NativeCraftComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UNativeCraftComponent : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool IsAllowMultipleInstance() const;
	UFUNCTION(BlueprintCallable)
	void SetIsAllowMultipleInstance(bool bIsAllowMultipleInstance);
	UFUNCTION(BlueprintCallable)
	bool IsActive() const;
	UFUNCTION(BlueprintCallable)
	void SetIsActive(bool bIsActive);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Description;

public:
	
	UNativeCraftComponent();

private:
	// Whether allow item or entity have multiple same class of components
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAllowMultipleInstance = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsActive = false;
};
