// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DInventoryComponent.h"
#include "EquipmentManagerComponent.generated.h"


class UHelmetMeta;
class UItemStack;
class UEquipmentRenderComponent;
class UEquipmentSlotComponent;
/*
 * UML Diagram link https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-class-diagram-tutorial/
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipUpdate, int32, Index);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipmentManagerComponent : public UDInventoryComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentManagerComponent();
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

	virtual void TransferSlots(int32 SourceIndex, UDInventoryComponent* SourceInventory, int32 DestinationIndex) override;

	UPROPERTY(BlueprintAssignable)
	FOnEquipUpdate OnEquipUpdate;
	
	/* 属性 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Equip Render")
	UEquipmentRenderComponent* EquipmentRenderComponent;

protected:


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual bool IsOccupied(UItemStack* Slot);
};
