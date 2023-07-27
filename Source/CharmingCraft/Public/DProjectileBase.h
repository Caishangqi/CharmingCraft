// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS(Abstract)
// 'ABSTRACT' marks this class as incomplete, keeping this out of certain dropdowns windows like SpawnActor in unreal Editor
class CHARMINGCRAFT_API ADProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category= "Effects")
	UParticleSystem* ImpactVFX;

	/*
	 *	球碰撞体积组件
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	USphereComponent* SphereComp;

	/*
	 *	投射物运动组件
	 *	这个组件给予一个初速度, 然后直线行走
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UProjectileMovementComponent* MoveComp;

	/*
	 *	粒子组件
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UParticleSystemComponent* EffectComp;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	// Not required for assignment, useful for expanding in Blueprint later on
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
