// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/Interact/NativeInteractActor.h"
#include "NativeLootEntity.generated.h"

class UDropTableData;

/*!
 * Experimental Class that pack all loot item into a single "Loot"
 * object, that useful when there are lot of loot item for a Creature
 *
 * TODO: Current not implement because the loot drop of a object is not
 * complex enough
 */
UCLASS()
class CHARMINGCRAFT_API ANativeLootEntity : public ANativeInteractActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANativeLootEntity();

	UFUNCTION(BlueprintCallable)
	void GenerateLootContent(TArray<UItemStack*> Content);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootMesh")
	TObjectPtr<USkeletalMeshComponent> LootMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootContent")
	TObjectPtr<UInventoryComponent> LootContent;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
