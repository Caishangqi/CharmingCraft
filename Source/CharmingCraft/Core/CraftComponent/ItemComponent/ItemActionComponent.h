// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/CraftComponent/NativeCraftComponent.h"
#include "CharmingCraft/Core/Skill/EquipmentSkill/ItemDynamicSkill.h"
#include "ItemActionComponent.generated.h"

class UItemStack;
class UNativeAction;
/**
 * 
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UItemActionComponent : public UNativeCraftComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Editor")
	FName ItemDynamicSkillName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Editor")
	TArray<TSubclassOf<UNativeAction>> ActionTemplateCollection;

public:
	UItemActionComponent();

	UFUNCTION(BlueprintCallable)
	bool SetActionSelected(UNativeAction* TargetAction);

	UFUNCTION(BlueprintCallable)
	TArray<UNativeAction*> GetActionByType(EItemDynamicSkillSlot ActionType);
	UFUNCTION(BlueprintCallable)
	TArray<EItemDynamicSkillSlot> GetTotalTypesActionInComponent();
	
	UFUNCTION(BlueprintCallable)
	bool AddActionToComponent(UNativeAction* TargetAction);
	
	UFUNCTION(BlueprintCallable)
	void CreateActionInstances();

	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintCallable)
	TArray<UNativeAction*> GetActionInstances();

	virtual void SetIsActive(bool bIsActive) override;

	UFUNCTION(BlueprintCallable)
	UItemStack * GetParentItemStack();

private:
	UPROPERTY()
	TArray<UNativeAction*> ActionInstances;
	
	void MappingActionContent(UNativeAction* TargetAction);
	
	TMap<EItemDynamicSkillSlot, TArray<UNativeAction*>> ActionInstanceMapping;

	UPROPERTY()
	TObjectPtr<UItemStack> OuterItemStack;
};
