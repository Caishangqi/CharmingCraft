// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "CharmingCraft/Object/Structs/model/EquipmentAnimation.h"
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
	TObjectPtr<UArrowComponent> EquipmentTopArrow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UArrowComponent> EquipmentBottomArrow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBoxComponent> EquipmentBoxComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UEquipmentAnimation> EquipmentAnimation;
	// Used in Ranged based Item, that may have multiple muzzles
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName,TObjectPtr<UArrowComponent>> SocketContext;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
