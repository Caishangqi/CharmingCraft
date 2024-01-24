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

	// Set of Buff Info
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UBuffInfo>> BuffList;

	UFUNCTION(BlueprintCallable)
	UBuffInfo* CreateBuffInfo(TSubclassOf<UBuffData> BuffDataClass, APawn* BuffInstigator,
	                          APawn* BuffTarget, bool AddAfterCreate, FHitData HitData,
	                          TMap<FName, int32> InternalData);

	UFUNCTION(Blueprintable, BlueprintCallable)
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
