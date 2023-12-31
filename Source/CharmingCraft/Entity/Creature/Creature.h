// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Interface/DGameplayInterface.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

class UDamageIndicator;
/*!
 *	The Base Class in Editor is BP_Creature, it add more component
 *	- DClickableActionComponentBP
 *
 *	TODO: The AI interface should write in this native class not inside the
 *	Editor BP_Creature
 */
UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API ACreature : public ACharacter, public IDamageable, public IDGameplayInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreature();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviourTree;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="UI")
	TObjectPtr<UDamageIndicator> DamageIndicator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attribute")
	TObjectPtr<UDAttributeComponent> CreatureAttributeComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData) override;
};
