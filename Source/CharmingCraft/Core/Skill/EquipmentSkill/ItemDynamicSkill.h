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
	SHIFT_INTERACT,
	INTERACT,
	PASSIVE,
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
