// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Structs/FDMaterial.h"
#include "Components/ActorComponent.h"
#include "ItemStack.generated.h"


class UItemMeta;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UItemStack : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemStack();
	UItemStack(FDataTableRowHandle Type);
	UItemStack(FDataTableRowHandle Type, int32 Amount);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "ItemStack Fields")
	int32 Amount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "ItemStack Fields")
	int32 Durability; //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "ItemStack Fields")
	FDataTableRowHandle Material; //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "ItemStack Fields")
	UItemMeta* ItemMeta;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
