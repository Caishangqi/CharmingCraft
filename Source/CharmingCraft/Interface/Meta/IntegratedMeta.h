// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/Item/Meta/ItemMeta.h"
#include "CharmingCraft/Object/Structs/model/FEquipmentAttribute.h"
#include "IntegratedMeta.generated.h"

/**
 * 
 */
class UEquipmentAnimation;
UCLASS()
class CHARMINGCRAFT_API UIntegratedMeta : public UItemMeta
{
	GENERATED_BODY()

public:
	UIntegratedMeta();

	UPROPERTY()
	FEquipmentAttribute EquipmentAttribute;
	
	/* Animation and Attack Stage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "LoadedAnimMontage")
	TObjectPtr<UEquipmentAnimation> LoadedAnimMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "CurrentAttackStage")
	int CurrentAttackStage;

	/* AnimMontage */
	UFUNCTION(BlueprintCallable)
	virtual FAttackStageAnimation GetCurrentAttackAnimationMontage();
	
	// Layout for UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Layout")
	TSubclassOf<UUserWidget> Layout;
};
