// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/DAbstractInterObjectPrototype.h"
#include "DropItem.generated.h"

class UBoxComponent;
class UItemStack;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADropItem : public ADAbstractInterObjectPrototype
{
	GENERATED_BODY()

public:
	ADropItem();
	void SetupCollision();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Drop Item Properties")
	TObjectPtr<UItemStack> ItemStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropIconMesh;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropModelMesh;
	// Collision for External Actor, because interact highlight and interact not handle by external actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* InvisibleCollision;

	virtual void PostInitializeComponents() override;

	void Initialize(UItemStack* PassItemStack);

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	virtual void BeginPlay() override;
};
