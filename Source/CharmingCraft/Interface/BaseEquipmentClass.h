// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEquipmentClass.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UBaseEquipmentClass : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UBaseEquipmentClass();

	/* Filed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Render")
	UStaticMesh* RenderedMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Basic Property")
	FString Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Basic Property")
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Equip Property")
	int32 OverAllArmors;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Equip Property")
	int32 OverAllResistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame

	/* Method */
};
