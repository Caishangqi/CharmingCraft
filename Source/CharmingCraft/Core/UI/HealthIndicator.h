// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IUIProcess.h"
#include "Components/WidgetComponent.h"
#include "HealthIndicator.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UHealthIndicator : public UWidgetComponent, public IUIProcess
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthIndicator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
