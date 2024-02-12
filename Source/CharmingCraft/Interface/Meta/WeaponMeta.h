// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntegratedMeta.h"
#include "CharmingCraft/Object/Structs/model/FEquipmentAttribute.h"
#include "WeaponMeta.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UWeaponMeta : public UIntegratedMeta
{
	GENERATED_BODY()

public:
	/* 模型 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Actor Model")
	TSubclassOf<AActor> WeaponActor;
	UPROPERTY()
	FEquipmentAttribute WeaponAttribute;

	/*!
	 * When done initialize Meta, the ItemPreviewRender should call the method
	 * after it BeginDeferredActorSpawnFromClass to assemble the meta stored component
	 * into target actor
	 * @param Actor The actor you want to assemble with different component parts
	 * @return Weather successful assemblies component 
	 */
	virtual bool AssembleComponent(AActor* Actor);

	virtual void UpdateRender(UWorld* RenderWorld) override;

	/* Animation and Attack Stage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "LoadedAnimMontage")
	TArray<TObjectPtr<UAnimMontage>> LoadedAnimMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "CurrentAttackStage")
	int CurrentAttackStage;
	/* AnimMontage */
	UFUNCTION(BlueprintCallable)
	UAnimMontage * GetCurrentAttackAnimationMontage();

public:
	virtual TSharedPtr<FJsonObject> SerializeToJson() override;
	virtual UObject* DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject) override;

	
};
