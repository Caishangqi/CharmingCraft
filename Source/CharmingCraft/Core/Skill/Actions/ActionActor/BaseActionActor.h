// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAction.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "GameFramework/Actor.h"
#include "BaseActionActor.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class CHARMINGCRAFT_API ABaseActionActor : public AActor, public IDamageable
{
	GENERATED_BODY()

public:
	// Who Generate the Action Actor, usually Player and Creature
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UDAction> InstigatorAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHitData ActionHitData;

	UPROPERTY(BlueprintReadWrite)
	TSet<TObjectPtr<AActor>> HitActors;
	
	UPROPERTY(BlueprintReadWrite)
	int32 ActionActorHealth;

	// Actual Collision box that detect collision
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USphereComponent> CollisionBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(BlueprintReadWrite)
	TSet<TObjectPtr<AActor>> IgnoreActors;

	// The "OnHit Actions" will start when ActionActor Perform OnHit
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UDAction>> OnHitActions;
	
	// The "OnHit Actions" will start when ActionActor Perform OnSpawn
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UDAction>> OnSpawnActions;

	// The "OnHit Actions" will start when ActionActor Perform OnTick
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UDAction>> OnTickActions;
	
public:
	// Sets default values for this actor's properties
	ABaseActionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Cycle")
	bool OnActionActorSpawn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Cycle")
	void OnActionActorTick();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Cycle")
	bool OnActionActorDestroy();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Event")
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Event")
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Cycle")
	bool OnActionActorHit();
};
