// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerAttributeWidget.generated.h"

class ANativePlayerCharacter;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ANativePlayerCharacter> Player;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
};
