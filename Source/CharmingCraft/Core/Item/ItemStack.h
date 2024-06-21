// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/CraftComponent/Interface/ComponentizedObjectInterface.h"
#include "CharmingCraft/Core/Save/Data/PersistentDataContainer.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "Components/ActorComponent.h"
#include "Data/FItemStack.h"
#include "ItemStack.generated.h"


class UNativeCraftComponent;
class UItem;
class UItemMeta;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UItemStack : public UPersistentDataContainer, public IComponentizedObjectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemStack();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	int32 Amount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	EMaterial Material; //
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="ItemStack InternalData")
	TSubclassOf<UItem> ItemClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "ItemStack Fields")
	UItemMeta* ItemMeta;

	UPROPERTY()
	TArray<UNativeCraftComponent*> Components;

	virtual UNativeCraftComponent* AddComponents_Implementation(UNativeCraftComponent* AddedComponents) override;
	virtual bool RemoveComponents_Implementation(UNativeCraftComponent* RemovededComponents) override;
	virtual TArray<UNativeCraftComponent*> GetObjectComponentsByClass_Implementation(TSubclassOf<UNativeCraftComponent> ComponentsClass) override;
	virtual TArray<UNativeCraftComponent*> GetObjectComponents_Implementation() override;
	
protected:


public:
	UItemStack* CopyData();

	// Factory Method
	/*!
	 * 
	 * @param Outer The Outer of the ItemStack Object
	 * @param ItemMaterial Base On ItemMaterial Create ItemStack
	 * @param SetAmount Init ItemStack with correspond amount
	 * @return UItemStack 
	 */
	UFUNCTION(BlueprintCallable)
	static UItemStack* CreateItemStackFromMaterial(UObject* Outer, const EMaterial ItemMaterial, const int32 SetAmount);
	/*!
	 * 
	 * @param Outer The Outer of the ItemStack Object
	 * @param ItemClassName Base On ItemClass Create ItemStack
	 * @param SetAmount Init ItemStack with correspond amount
	 * @return UItemStack 
	 */
	UFUNCTION(BlueprintCallable)
	static UItemStack* CreateItemStackFromItemClass(UObject* Outer, TSubclassOf<UItem> ItemClassName,
	                                                const int32 SetAmount);

public:
	UFUNCTION(BlueprintCallable)
	UItem* GetItemClass() const;

	/* Serialize and Deserialize */
public:
	// Native C++ Serialization
	virtual TSharedPtr<FJsonObject> SerializeToJson() override;
	virtual UObject* DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject) override;
};
