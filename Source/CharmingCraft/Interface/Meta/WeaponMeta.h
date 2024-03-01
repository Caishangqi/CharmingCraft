// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntegratedMeta.h"
#include "WeaponMeta.generated.h"

/**
 * 
 */
struct FAttackStageAnimation;
UCLASS()
class CHARMINGCRAFT_API UWeaponMeta : public UIntegratedMeta
{
	GENERATED_BODY()

public:


	/*!
	 * When done initialize Meta, the ItemPreviewRender should call the method
	 * after it BeginDeferredActorSpawnFromClass to assemble the meta stored component
	 * into target actor
	 * @param Actor The actor you want to assemble with different component parts
	 * @return Weather successful assemblies component 
	 */
	virtual bool AssembleComponent(AActor* Actor);

public:
	virtual TSharedPtr<FJsonObject> SerializeToJson() override;
	virtual UObject* DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject) override;
};
