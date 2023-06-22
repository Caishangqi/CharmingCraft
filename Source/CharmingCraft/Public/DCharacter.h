// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //核心UE运行环境下的要素
#include "GameFramework/Character.h"
#include "DCharacter.generated.h" //自己生成的，恶心代码

UCLASS() //Part of UE Property System
class CHARMINGCRAFT_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*
	 * The override keyword is an optional keyword
	 * used to indicate that a virtual function is
	 * overridden in a derived class.
	 */

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
