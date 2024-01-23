// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffInfo.h"
#include "UObject/Object.h"
#include "BuffHandlerComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBuffHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuffHandlerComponent();

	// Set of Buff Info
	UPROPERTY()
	TArray<TObjectPtr<UBuffInfo>> BuffList;

	UFUNCTION(BlueprintCallable)
	UBuffInfo* CreateBuffInfo(TSubclassOf<UBuffData> BuffDataClass, AActor* BuffInstigator, AActor* BuffTarget,
	                          bool AddAfterCreate, FHitData HitData);

	UFUNCTION(Blueprintable, BlueprintCallable)
	void AddBuff(UBuffInfo* BuffInfo, FHitData HitData);
	UFUNCTION(Blueprintable, BlueprintCallable)
	void RemoveBuff(UBuffInfo* BuffInfo, FHitData HitData);

	void BuffTickAndRemove(float DeltaTime);
	void Update(float DeltaTime);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<UBuffInfo> SearchBuff(int32 Id);
};
