// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDynamicSkill.generated.h"

/**
 * 
 */
class UDAction;

UENUM(BlueprintType)
enum class EItemDynamicSkillSlot : uint8
{
	// whe player open Item detail panel click "Use" action bottom
	USE, 
	SHIFT, 
	SHIFT_INTERACT,
	RIGHT_CLICK,
	HOTBAR_CAST,
	// When player interact some object, Action component will automatically
	// start the Actions
	INTERACT,
	// ActionComponent will automatically run the action when related
	// ItemStack equipped on inventory
	PASSIVE,
	// ActionComponent will automatically run the action at some condition
	// depend by Action logic
	ON_HIT,
};


UCLASS()
class CHARMINGCRAFT_API UItemDynamicSkill : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Editor")
	FName ItemDynamicSkillName;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UDAction>> DynamicSkills;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Editor")
	TArray<TSubclassOf<UDAction>> DynamicSkillsContent;

public:
	UItemDynamicSkill();

	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintCallable)
	bool AddDynamicSkillToSlot(TSubclassOf<UDAction> ActionClass);
};
