// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwordActor.generated.h"
class UArrowComponent;
/*!
 * This Class is for Integrate Sword, the sword have 5 parts, each parts is
 * StaticMeshComponent, player could modify each parts into different subpart
 * with different materials, for example blade can have different sub category
 * such as Basic Blade, Heavy Blade.
 *
 * Assemble 5 parts of sword is the sword model actor, use this actor and save
 * to sword meta, when equip to player main hand - Attach to Component - to player
 * main hand socket
 *
 * DataStructure of Meta is same but have additional Actor field, use UEquipPartComponent
 * filed StaticMesh to assemble Sword Actor
 */
UCLASS()
class CHARMINGCRAFT_API ASwordActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwordActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	/* Sword Mesh Part */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Sword;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Blade;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Fuller;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Guard;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Hilt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Pommel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UArrowComponent* SwordTopArrow;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UArrowComponent* SwordBottomArrow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
