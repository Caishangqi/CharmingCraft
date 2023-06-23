// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //核心UE运行环境下的要素
#include "GameFramework/Character.h"
#include "DCharacter.generated.h" //自己生成的，恶心代码

//便于编译效率
class UCameraComponent;
class USpringArmComponent;

UCLASS() //Part of UE Property System
class CHARMINGCRAFT_API ADCharacter : public ACharacter
{
	GENERATED_BODY() //确保放在第一行

public:
	// Sets default values for this character's properties
	ADCharacter();
	/*
	 * Constructor called when the Object is initialized
	 * then call BeginPlay() when everything is loaded
	 */

protected:
	// Called when the game starts or when spawned (or when the level load it)
	virtual void BeginPlay() override;
	/*
	 * The override keyword is an optional keyword
	 * used to indicate that a virtual function is
	 * overridden in a derived class.
	 */

	/*!
	 * 角色的向前移动函数
	 * @param value 传入scale值 0.0 - 1.0
	 * 
	 */
	virtual void MoveForward(float value);

	UPROPERTY(VisibleAnywhere) // 把SpringArmComp暴露给编辑器中的蓝图和各个部分
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
