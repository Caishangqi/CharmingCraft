// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "NativeItemAction.generated.h"
class ADCharacter;
class UCharmingCraftInstance;
class UItemStack;
/**
 * Dynamic Item Skill Template, the action need pass an UItemStack allow
 * Action to read Item Attribute
 *
 * Use Case 1: The Hp potion is an item, but it have different item meta
 * between different level of Hp potion, the Action could be "drink potion"
 * but the action need to read internal ItemMeta to restore player different
 * amount of health.
 *
 * Use Case 2 (Not implement yet): the Reward chest could have different drop
 * table, when player receive a reward chest or package, they could start the
 * action like "Open rewards" then the action need to pass the chest item to
 * read drop table in the ItemMeta to decided the rewards
 */
UCLASS()
class CHARMINGCRAFT_API UNativeItemAction : public UDAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category= "Bind ItemStack", BlueprintReadWrite)
	TObjectPtr<UItemStack> BindItemStack;

	// Who cast the Action
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APawn> CastInstigatorPlayer;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UCharmingCraftInstance> GameInstance;


public:
	UNativeItemAction();
	
	virtual void StartAction_Implementation(APawn* Instigator) override;
};
