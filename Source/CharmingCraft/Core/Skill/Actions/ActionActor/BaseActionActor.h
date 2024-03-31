// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "GameFramework/Actor.h"
#include "BaseActionActor.generated.h"

class UDAction;
class UProjectileMovementComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class ActionActorType : uint8
{
	Attack,
	Skill,
	OnSpawn,
	OnDestroy,
	OnBeHit,
};

/*!
 *	Struct that use for interchange data between Actions and Action Actor / Entity
 */
USTRUCT(BlueprintType)
struct FActionActorData
{
	GENERATED_BODY()

public:

	FActionActorData():ActionHitData(){};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHitData ActionHitData;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UObject> Parent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UDAction> InstigatorAction;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UDAction> OnHitCastAction;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UDAction> OnDestroyCastAction;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UDAction> OnSpawnCastAction;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UDAction> OnTickCastAction;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSet<TObjectPtr<AActor>> IgnoreActors;

	// Who Own the Action Entity, usually the instigator character
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<APawn> ActionActorOwner;
	
};


UCLASS()
class CHARMINGCRAFT_API ABaseActionActor : public AActor, public IDamageable
{
	GENERATED_BODY()

public:
	// Which Actions Generate the Action Actor
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UDAction> InstigatorAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHitData ActionHitData;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UObject> Parent;

	// Who Own the Action Entity, usually the instigator character
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<APawn> ActionActorOwner;
	
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
	TObjectPtr<UDAction> OnHitActions;

	// The "OnHit Actions" will start when ActionActor Perform OnSpawn
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UDAction> OnSpawnActions;

	// The "OnHit Actions" will start when ActionActor Perform OnTick
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UDAction> OnTickActions;

public:
	// Sets default values for this actor's properties
	ABaseActionActor();

	/*!
	 * Inject the FActionActorData into ActionActor, FActionActorData contain the lifecycle
	 * data and attribute need by ActionActor.
	 *
	 * @note {the function should not called by user}
	 * @param ActionActorData The FActionActorData that prepare to inject to ActionActor
	 * @return whether the data set properly
	 */
	UFUNCTION(BlueprintNativeEvent)
	bool InjectActionData(FActionActorData ActionActorData);

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

	/*!
	 * Apply Storage HitActions to target
	 * @param OtherActor The Other Actor that was hit by the Action Entity
	 * @return true if other actor valid
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category= "Cycle")
	bool OnActionActorHit(AActor* OtherActor);
};
