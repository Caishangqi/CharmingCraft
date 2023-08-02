// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Interface/DAbstractInterObjectPrototype.h"
#include "DChestContainer.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADChestContainer : public ADAbstractInterObjectPrototype
{
	GENERATED_BODY()

public:
	/* 属性 */
	UPROPERTY(EditAnywhere) //现在可以在编辑器中编辑这个变量, 这个变量可以控制箱子开合pitch
	float TargetPitch;


	/* 方法 */
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	ADChestContainer();

protected:
	/* 属性 */
	//箱子底部
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	//箱子顶部
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	/* 方法 */
};
