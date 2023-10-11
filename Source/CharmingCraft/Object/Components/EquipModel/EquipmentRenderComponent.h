// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentRenderComponent.generated.h"

class UEquipmentManagerComponent;
class ADCharacter;
class UCharacterSocket;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, Blueprintable))
class CHARMINGCRAFT_API UEquipmentRenderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentRenderComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "PlayerSkeletonSocket")
	TArray<UCharacterSocket*> PlayerSkeletonSocket;

	UPROPERTY()
	ADCharacter* Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable) // 必须是BlueprintCallable才能绑定委托
	virtual void UpdateRender(int32 Index);

	UFUNCTION(BlueprintCallable)
	UEquipmentRenderComponent* Initialize(int32 Size, ADCharacter* Player);
};
