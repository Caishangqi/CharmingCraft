// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Hoe.generated.h"

/**
 * 
 */
class UBaseBuildModel;
UCLASS()
class CHARMINGCRAFT_API UHoe : public UEquipment
{
	GENERATED_BODY()
public:
	UHoe();

	// Visual enhancement tool specific property, generate additional Frame Actor
	// when equipped, equip hoe would generate HoeBuildModel that tell player
	// which grid can be plowing.
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	TSubclassOf<UBaseBuildModel> BuildModel;
	
	virtual void OnEquip(UObject* Instigator, UItemStack* OnEquipItem) override;
	virtual void UnEquip(UObject* Instigator, UItemStack* UnEquipItem) override;
};
