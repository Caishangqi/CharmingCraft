// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NativeScriptObject.generated.h"

UENUM(BlueprintType)
enum class EScriptState : uint8
{
	Ready,
	Running,
	Suspend,
	Remove
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API UNativeScriptObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UObject> ParentScriptActorClass;
	// The "Outer" that response for this ScriptObject
	// handle the lifetime and edxecution of the script object instance
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UObject> ParentScriptActor;
	// The Object that create the ScriptObject, logically
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UObject> Instigator;
	// The state of script
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EScriptState ScriptState;
	// Whether enable OnScriptTick function
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bEnableScriptTick = false;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool StartScript(UObject* InstigatorObject);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool StopScript(UObject* InstigatorObject);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnScriptTick(UObject* InstigatorObject);
};
