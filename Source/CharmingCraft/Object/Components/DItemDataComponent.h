// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Interface/DItemInteractInterface.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "DItemDataComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UDItemDataComponent : public UActorComponent, public IDItemInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDItemDataComponent();

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDataTableRowHandle ItemID;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Quantity;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
