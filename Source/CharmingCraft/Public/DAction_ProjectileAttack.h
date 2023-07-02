// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "DAction_ProjectileAttack.generated.h"

/**
 * 
 */
class UAnimMontage;
class UParticleSystem;

UCLASS()
class CHARMINGCRAFT_API UDAction_ProjectileAttack : public UDAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category= "Attack")
	TSubclassOf<AActor> ProjectileClass; //stack 上的变量，在UE编辑器中被指定抛射物

	UPROPERTY(VisibleAnywhere, Category= "Effects")
	FName HandSocketName;

	UPROPERTY(EditAnywhere, Category= "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category= "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere, Category= "Attack")
	UParticleSystem* CastingEffect;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);
	
public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

	UDAction_ProjectileAttack();
};
