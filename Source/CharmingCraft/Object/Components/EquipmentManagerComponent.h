// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentManagerComponent.generated.h"


class UHelmetMeta;
class UItemStack;
class UEquipmentRenderComponent;
class UEquipmentSlotComponent;
/*
 * UML Diagram link https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-class-diagram-tutorial/
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer);

	/* 属性 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Equip Slot")
	UItemStack* HelmetSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Equip Slot")
	UItemStack* ChestPlateSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Equip Slot")
	UItemStack* LeggingSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Equip Slot")
	UItemStack* BootSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Equip Render")
	UEquipmentRenderComponent* EquipmentRenderComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual bool IsOccupied(UItemStack* Slot);
};
