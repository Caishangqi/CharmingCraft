// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Item.generated.h"

/**
 * 
 */
class UItemStack;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	int32 MaxStackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	UStaticMesh* StaticMesh;

public: // Methods
	UFUNCTION(BlueprintCallable)
	virtual void OnItemInteract(UItemStack* InteractItemStack, AActor* Instigator, AActor* ItemActorEntity);
	UFUNCTION(BlueprintCallable)
	virtual void EndItemInteract();
};
