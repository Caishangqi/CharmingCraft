// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "EquipmentEntityActor.generated.h"
class UBoxComponent;
class UArrowComponent;
UCLASS()
class CHARMINGCRAFT_API AEquipmentEntityActor : public AItemEntityActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquipmentEntityActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UArrowComponent* EquipmentTopArrow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UArrowComponent* EquipmentBottomArrow;

	TObjectPtr<UBoxComponent> EquipmentBoxComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
