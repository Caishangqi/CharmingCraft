// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSocket.h"
#include "MainHandSocket.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CHARMINGCRAFT_API UMainHandSocket : public UCharacterSocket
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* MainHandSocket;

	UPROPERTY(BlueprintReadWrite)
	AActor* AttachedActor;

	UMainHandSocket();

	virtual void UpdateRender() override;

	virtual void BindSocket() override;
};
