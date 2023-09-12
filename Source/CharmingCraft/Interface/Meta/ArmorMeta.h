// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntegratedMeta.h"
#include "ArmorMeta.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UArmorMeta : public UIntegratedMeta
{
public:
	/* 作为初始化默认盔甲模型,后续根据盔甲部件进行修改 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Render")
	UStaticMesh* RenderedMesh;

	GENERATED_BODY()
};
