// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseBuildModel.generated.h"

class UWorld;
class UBuildModuleManager;
/**
 * 
 */
class AFrameActor;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API UBaseBuildModel : public UObject
{
	GENERATED_BODY()

public:
	UBaseBuildModel();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool StartTrace(UObject* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool StopTrace(UObject* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ActivateBuildModel(UObject* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool DeactivateBuildModel(UObject* Instigator);

	virtual UWorld* GetWorld() const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BuildModelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BuildRange = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AFrameActor> FrameActorClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AFrameActor> FrameActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBuildModuleManager> BuildModuleManager;
	// Whether the BuildModel is perform logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActivate;
};
