// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Core/Skill/EquipmentSkill/ItemDynamicSkill.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CharmingCraft/Core/Skill/Actions/ActionActor/BaseActionActor.h"
#include "DAction.generated.h"

/**
 * 
 */
class UWorld;
/*
 *	Because we drive the Class from UObject, without UCLASS(Blueprintable), we can
 *	not make child classes from as Action
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoolComplete, AActor*, InstigatorPawn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoolCStart, AActor*, InstigatorPawn);

UCLASS(Blueprintable)
class CHARMINGCRAFT_API UDAction : public UObject
{
	GENERATED_BODY()

public:
	/* Action nickname to start/stop without a reference to the object */
	UPROPERTY(EditDefaultsOnly, Category= "Action", BlueprintReadWrite)
	FName ActionName; // FName is hashed used in game, highly optimized

	/* Resource:
	 * https://www.reddit.com/r/PixelArt/comments/ikhnb8/16x16_ability_icons_based_off_dnd_i_really/
	 * https://black-minecraft.com/resources/supreme-icons-pack-100-texture-icons.1910/
	 */

	// Useful when Action's outer is not ActionComponent
	UPROPERTY(Category= "Handler", BlueprintReadWrite)
	TObjectPtr<UDActionComponent> Handler;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	UTexture2D* SkillIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Ignore Target")
	TSet<TObjectPtr<AActor>> IgnoreTargetActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCooling = false;

	// For ItemDynamicSkill
	// ItemSkill is display to player but some not unlock
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Dynamic Skill")
	bool bIsUnlocked = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Type")
	EItemDynamicSkillSlot SkillType;

	/* Default Cooldown */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolDown = 5.0f;

	// Use when multiple ActionActor triggered type action triggered
	// same time. For example, sword have OnHitAction, also armour have
	// the priority determine who's Action trigger first
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Priority;

	UFUNCTION(BlueprintCallable, Category= "Action")
	UDActionComponent* GetOwningComponent() const;


	/*
	 *	BlueprintNativeEvent it means that it has a native implementation which is C++,
	 *	so we can implement it in cpp, also it allows blueprints to overwrite it.
	 *
	 *	Also, because we mark this BlueprintNativeEvent, the implementation will be
	 *	_Implementation
	 *
	 *	@see UDAction::StartAction_Implementation(AActor* Instigator)
	 */
	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	void StartAction(APawn* Instigator); // Passing who is responsible for starting the action

	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	bool CanStart(APawn* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action")
	void StopAction(APawn* Instigator);

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category= "Action")
	bool IsRunning() const;
	UFUNCTION(BlueprintCallable, Category= "Timer")
	void StartCoolDown();
	UFUNCTION(BlueprintCallable, Category= "Timer")
	void CooldownFinished();
	UFUNCTION(BlueprintCallable, Category= "Timer")
	void ResetCoolDown();
	UFUNCTION(BlueprintCallable, Category= "Timer")
	float GetRemainCooldown();

	/*!
	 * Get the FActionActorData if the action is going to spawn a
	 * ActionActor.
	 * @return FActionActorData that prepare to spawn ActionActor
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action Actor")
	FActionActorData GetActionActorData();
	/*!
	 * Get the Action HitData, use could implement this method to decide
	 * each actions custom HitData, for example, you could get a HitData
	 * based on item attribute or based on character level and attributes
	 * @return FHitData that action will hold and apply to target or else
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action Actor")
	FHitData GetActionHitData();
	/* Event */
	UPROPERTY(BlueprintAssignable)
	FOnCoolComplete OnCoolComplete;

	UPROPERTY(BlueprintAssignable)
	FOnCoolComplete OnCoolStart;

protected:
	/* Tags added to owning actor when activated, removed when action stops */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;
	/* Action can only start if OwningActor has none of these Tags applied */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	FTimerHandle TimerHandle_Cooldown;

	UPROPERTY()
	TObjectPtr<AActor> CachedInstigator;

	bool bIsRunning;
};
