// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/DAbstractInterObjectPrototype.h"
#include "DropItem.generated.h"

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

	// 添加一个USceneComponent作为根组件
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Drop Item Properties")
	UItemStack* ItemStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropIconMesh;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropModelMesh;

	virtual void PostInitializeComponents() override;

	void Initialize(UItemStack* PassItemStack);

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	virtual void BeginPlay() override;
};
