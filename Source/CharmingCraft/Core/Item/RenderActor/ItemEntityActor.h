// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "GameFramework/Actor.h"
#include "ItemEntityActor.generated.h"

UCLASS()
class CHARMINGCRAFT_API AItemEntityActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemEntityActor();

	// The Owner of this ItemActor, typically belong to An ItemMeta
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UItemMeta> OwnItemMeta;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
