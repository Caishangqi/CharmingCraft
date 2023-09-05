// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Interface/DAbstractInterObjectPrototype.h"
#include "WorkBench.generated.h"

class UWorkBenchComponent;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API AWorkBench : public ADAbstractInterObjectPrototype
{
	GENERATED_BODY()

public:
	AWorkBench();

	/* 方法 */
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	/* 属性 */
	// 工作台底部
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WorkBenchMesh;

	// 工作台全息
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* HologramMesh;

	// 工作台处理组件
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UWorkBenchComponent* WorkBenchComponent;
};
