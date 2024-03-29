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
	// 使用时
	SHIFT,
	// Shift时
	SHIFT_INTERACT,
	// Shift + 使用 时
	RIGHT_CLICK,
	// 右键时
	HOTBAR_CAST,
	// 技能栏释放
	// When player interact some object, Action component will automatically
	// start the Actions
	INTERACT,
	// 交互时
	// ActionComponent will automatically run the action when related
	// ItemStack equipped on inventory
	PASSIVE,
	// 被动持续增益 (例如盔甲装备后增加生命恢复,这需要与Buff系统建立链接)
	// ActionComponent will automatically run the action at some condition
	// depend by Action logic
	ON_HIT,
	// 武器命中时 (单独武器命中技能,例如弓箭和不同的命中效果,寒霜,火焰,中毒等)
	// When player success start attack status and the action will trigger
	// to the target of player hit
	ON_ATTACK // 玩家攻击命中时 (玩家攻击命中后技能,这里只玩家武器命中触发的额外技能,例如披风上的玩家攻击时连锁闪电)
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
