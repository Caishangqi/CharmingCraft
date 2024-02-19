// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerAttributeWidget.generated.h"

class ADCharacter;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UPlayerAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ADCharacter> Player;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
};
