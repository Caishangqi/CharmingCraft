// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NativeCraftComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API UNativeCraftComponent : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool SetUpAttachment(UObject* ParentObject);
	UFUNCTION(BlueprintCallable)
	UObject* GetParentAttachedObject();

	UFUNCTION(BlueprintCallable)
	bool IsAllowMultipleInstance() const;
	UFUNCTION(BlueprintCallable)
	void SetIsAllowMultipleInstance(bool bIsAllowMultipleInstance);
	UFUNCTION(BlueprintCallable)
	bool IsActive() const;
	UFUNCTION(BlueprintCallable)
	virtual void SetIsActive(bool bIsActive);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Description;

public:
	virtual void PostInitProperties() override;
	UNativeCraftComponent();

private:
	// Whether allow item or entity have multiple same class of components
	UPROPERTY(EditAnywhere)
	bool bIsAllowMultipleInstance = true;

	UPROPERTY(EditAnywhere)
	bool bIsActive = false;

	// The Object that the components attached to different with Outer
	// the outer is the creator
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UObject> ParentAttachedObject;
};
