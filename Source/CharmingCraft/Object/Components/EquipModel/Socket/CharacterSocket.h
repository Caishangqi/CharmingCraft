// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterSocket.generated.h"

class ADCharacter;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UCharacterSocket : public UObject
{
	GENERATED_BODY()

public:
	UClass* SocketBindClass;
	FName SocketName;
	int32 SocketIndex;

	UPROPERTY()
	ADCharacter* Owner;
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;

	virtual UCharacterSocket* Initialize(ADCharacter* Player);

	virtual void UpdateRender();

	virtual void BindSocket();
};
