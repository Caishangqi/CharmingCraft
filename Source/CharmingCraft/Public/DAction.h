// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	UTexture2D* SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCooling = false;

	/* Default Cooldown */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolDown = 5.0f;

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
	void StartAction(AActor* Instigator); // Passing who is responsible for starting the action

	UFUNCTION(BlueprintNativeEvent, Category= "Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action")
	void StopAction(AActor* Instigator);

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
