// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Container.h"
#include "Chest.generated.h"

class UDInventoryComponent;
/**
 * TODO: Consider rewrite the Interface and Base Class of Both
 * WorkBench and Container
 */
UCLASS()
class CHARMINGCRAFT_API AChest : public AContainer
{
	GENERATED_BODY()

public:
	/* 属性 */
	UPROPERTY(EditAnywhere) //现在可以在编辑器中编辑这个变量, 这个变量可以控制箱子开合pitch
	float TargetPitch;

	/* 方法 */
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	AChest();

protected:
	/* 属性 */
	//箱子底部
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	//箱子顶部
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	/* 方法 */
	/* 属性 */
};
