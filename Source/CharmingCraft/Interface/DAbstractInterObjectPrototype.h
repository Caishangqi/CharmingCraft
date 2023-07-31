// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAbstractObjectPrototype.h"
#include "DGameplayInterface.h"
#include "DAbstractInterObjectPrototype.generated.h"

class UDClickableActorComponent;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADAbstractInterObjectPrototype : public ADAbstractObjectPrototype, public IDGameplayInterface
{
	GENERATED_BODY()

	/* 属性 */
public:
	UPROPERTY(BlueprintReadWrite, Category="Interaction")
	int32 MinimumInteractRange; //Can beautiful handle in Enumeration

	UPROPERTY(BlueprintReadWrite, Category="Interaction")
	bool bIgnoreRangeToInteract;

	UPROPERTY(BlueprintReadWrite, Category="Interaction")
	bool bIsAllowToInteract;


	/* 方法 */
	ADAbstractInterObjectPrototype();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
