// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputMappingContext.h"
#include "CharmingCraft/Core/GameMode/Enum/EPlayerMode.h"
#include "PlayerModeBase.generated.h"

/**
 * 
 */
class UPlayerModeManager;

UCLASS(Blueprintable, BlueprintType)
class CHARMINGCRAFT_API UPlayerModeBase : public UObject
{
	GENERATED_BODY()

public:
	UPlayerModeBase();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="默认")
	EPlayerMode ModeName = EPlayerMode::DEFAULT;


	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="默认")
	TSoftObjectPtr<UInputMappingContext> ModeMappingContext;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UPlayerModeManager> ParentModeManager;
	UFUNCTION(BlueprintCallable)
	void UpdateControllerMappingContext(EPlayerMode FromGameMode, ACharacter* Instigator, EPlayerMode NewPlayerMode);
	UFUNCTION(BlueprintCallable)
	UPlayerModeBase* BindDelegate();

protected:
	FString EnumClassToString(EPlayerMode EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EPlayerMode>();
		if (!EnumPtr)
		{
			return FString("Invalid");
		}
		return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
	}
};
