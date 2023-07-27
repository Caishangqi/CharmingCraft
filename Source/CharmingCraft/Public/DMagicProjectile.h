// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DProjectileBase.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "DMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class CHARMINGCRAFT_API ADMagicProjectile : public ADProjectileBase
{
	GENERATED_BODY()

public:
	
	// Sets default values for this actor's properties
	ADMagicProjectile();
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* GameTags */
	UPROPERTY(EditDefaultsOnly,Category = "Damage")
	FGameplayTag ParryTag;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
