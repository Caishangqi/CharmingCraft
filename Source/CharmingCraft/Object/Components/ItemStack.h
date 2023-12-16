// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "CharmingCraft/Object/Structs/FDMaterial.h"
#include "Components/ActorComponent.h"
#include "ItemStack.generated.h"


class UItem;
class UItemMeta;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UItemStack : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemStack();

	UFUNCTION(BlueprintCallable)
	UItemStack* Initialize(EMaterial Type, int32 Amount);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	int32 Amount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	EMaterial Material; //
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ItemStack InternalData")
	TSubclassOf<UItem> ItemClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	TSubclassOf<UItemMeta> ItemMetaClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	UItemMeta * ItemMeta;

protected:


public:
	UFUNCTION(BlueprintCallable)
	bool SynchronizeData();
	UItemStack* CopyData();

public:
	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintCallable)
	UItem* GetItemClass() const;
};
