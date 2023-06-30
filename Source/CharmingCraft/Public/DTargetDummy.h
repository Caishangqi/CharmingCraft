// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAttributeComponent.h"
#include "GameFramework/Actor.h"
#include "DTargetDummy.generated.h"
class UDAttributeComponent;

UCLASS()
class CHARMINGCRAFT_API ADTargetDummy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADTargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UDAttributeComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UDAttributeComponent* OwningComp, float HewHealth, float Delta);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
