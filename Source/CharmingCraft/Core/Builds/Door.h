// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entry.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "Door.generated.h"

UCLASS(Blueprintable)
class CHARMINGCRAFT_API ADoor : public AInteractObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString DestinationName;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Door")
	TObjectPtr<UEntry> DestinationEntry;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bTeleportToDefaultExit;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bTeleportToAnotherDoor;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AActor> DoorInternalCacheTarget;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool CanTeleportToDestination(APawn* TargetPawn);
	UFUNCTION(BlueprintCallable)
	bool TeleportToDestination(APawn* TargetPawn, AActor* Actor);
	UFUNCTION(BlueprintCallable)
	void PostDoorInteract(APawn* TargetPawn);
};
