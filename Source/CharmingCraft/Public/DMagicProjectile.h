// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class CHARMINGCRAFT_API ADMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMagicProjectile();

protected:

	/*
	 *	球碰撞体积组件
	 */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	/*
	 *	投射物运动组件
	 *	这个组件给予一个初速度, 然后直线行走
	 */
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	/*
	 *	粒子组件
	 */
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
