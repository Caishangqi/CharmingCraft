// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/Enum/EItemType.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "Item.generated.h"

/**
 * 
 */
class AItemEntityActor;
class UItemStack;
class UItemMeta;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	EMaterial Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	TSubclassOf<UItemMeta> ItemMetaClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	TSubclassOf<AItemEntityActor> DefaultItemEntityActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Description")
	FText DescribeText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Render")
	FTransform RenderSpecifyTransform;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Render")
	int32 OrthoWidth;

public: // Methods

	UItem();
	UFUNCTION(BlueprintCallable)
	virtual void OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator);
	UFUNCTION(BlueprintCallable)
	virtual void EndItemInteract();
};
