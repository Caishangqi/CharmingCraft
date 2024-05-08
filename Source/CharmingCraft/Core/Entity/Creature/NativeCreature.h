// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "../Core/Interact/Interface/DGameplayInterface.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "CharmingCraft/Core/UI/IUIProcess.h"
#include "GameFramework/Character.h"
#include "NativeCreature.generated.h"

class UDropTableData;
class UInventoryComponent;
class UDActionComponent;
class UHealthIndicator;
class UDamageIndicator;
class UBuffHandlerComponent;
/*!
 *	The Base Class in Editor is BP_Creature, it add more component
 *	- DClickableActionComponentBP
 *
 *	TODO: The AI interface should write in this native class not inside the
 *	Editor BP_Creature
 */
UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API ANativeCreature : public ACharacter, public IDamageable, public IMouseInteractInterface,
                                          public IUIProcess, public IGameplayTagAssetInterface, public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANativeCreature();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviourTree;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TObjectPtr<UDamageIndicator> DamageIndicator;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TObjectPtr<UHealthIndicator> HealthIndicator;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Action")
	TObjectPtr<UDActionComponent> ActionComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attribute")
	TObjectPtr<UDAttributeComponent> CreatureAttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Buff")
	TObjectPtr<UBuffHandlerComponent> BuffHandlerComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="HitResponseMontage")
	TMap<EDamageResponse, TObjectPtr<UAnimMontage>> HitResponseMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;
public: // Data

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Spawn")
	FVector SpawnPoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Spawn")
	bool bReturnToSpawn = true;
	// Drop
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Drop")
	TSubclassOf<UDropTableData> DropTableData;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Drop")
	bool DropLoot = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Tags")
	FGameplayTagContainer GameplayTags;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData) override;

	UFUNCTION(BlueprintCallable)
	virtual void HandleDamageIndicator_Implementation(FHitData HitData) override;
	UFUNCTION(BlueprintCallable)
	virtual void HandleHealthChanged_Implementation(APawn* InstigatorPawn, UDAttributeComponent* OwningComp,
	                                                float Health, float HealthDelta) override;
	UFUNCTION(BlueprintCallable)
	virtual void HandleDeath_Implementation(APawn* InstigatorPawn) override;
	UFUNCTION(BlueprintCallable)
	virtual bool IsDead_Implementation() override;

	/* Debug */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HitReaction(EDamageResponse Response);

	/* Core Management Object*/
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
	virtual UWorldManager* GetWorldManager_Implementation() override;
};
