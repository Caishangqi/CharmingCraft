// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffInfo.h"
#include "UObject/Object.h"
#include "BuffHandlerComponent.generated.h"

/**
 * 

*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBuffAddToBuffList, UBuffInfo*, BuffInfo, FHitData, HitData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBuffAddToBuffListRepeat, UBuffInfo*, BuffInfo, FHitData, HitData);

UCLASS()
class CHARMINGCRAFT_API UBuffHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuffHandlerComponent();

	// Set of Buff Info, if Buff Instance > 50 consider use link-list
	// and apply Quick Sort or Merge Sort
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UBuffInfo>> BuffList;

	/*!
	 * Add Buff to Buff List
	 * @param BuffInfo The Buff instance
	 * @param HitData The HitData that need handle
	 */
	void AddBuff(UBuffInfo* BuffInfo, FHitData HitData);
	void UpdateBuffDuration(UBuffInfo* BuffInfo);
	UFUNCTION(Blueprintable, BlueprintCallable)
	void RemoveBuff(UBuffInfo* BuffInfo, FHitData HitData);

	void BuffTickAndRemove(float DeltaTime);
	void Update(float DeltaTime);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/* Event */
	// UI
	UPROPERTY(BlueprintAssignable)
	FOnBuffAddToBuffList OnBuffAddToBuffList;

	UPROPERTY(BlueprintAssignable)
	FOnBuffAddToBuffListRepeat OnBuffAddToBuffListRepeat;

private:
	TObjectPtr<UBuffInfo> SearchBuff(int32 Id);
};
