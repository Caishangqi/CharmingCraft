// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentSlotComponent.generated.h"


class UBaseEquipmentClass;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipmentSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Equipment")
	AActor* Equipment;
	
	bool bIsOccupied = false;

	// Sets default values for this component's properties
	UEquipmentSlotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UpdateOccupied();
};
