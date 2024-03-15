// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Data/FPlaceValidation.h"
#include "UObject/Object.h"
#include "FrameInfoTemplate.generated.h"

/**
 * Template Class that handle different Overlap event base on Mode
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UFrameInfoTemplate : public UObject
{
	GENERATED_BODY()

public:
	// Material indicate different type of Collied
	// For example, Collied usually red, not collied is green
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EBuildCollidedType, UMaterialInstance*> TemplateStyle;
	UFUNCTION(Blueprintable, BlueprintNativeEvent, BlueprintCallable)
	void ChangeTemplateStyle(EBuildCollidedType Style, AFrameActor* Parent);
	UFUNCTION(Blueprintable, BlueprintNativeEvent, BlueprintCallable)
	void OnOverlapBeginStyle(EBuildCollidedType Style, AFrameActor* Parent);
	UFUNCTION(Blueprintable, BlueprintNativeEvent, BlueprintCallable)
	void OnOverlapEndStyle(EBuildCollidedType Style, AFrameActor* Parent);
	// Some times you want to set default style based on some parameter
	UFUNCTION(Blueprintable, BlueprintNativeEvent, BlueprintCallable)
	void SetDefaultTemplateStyle(AFrameActor* Parent);
	// Tick Function called by Frame actor, use to update style
	// not from event system
	UFUNCTION(Blueprintable, BlueprintNativeEvent, BlueprintCallable)
	void UpdateAppearance(AFrameActor* Parent);
};
