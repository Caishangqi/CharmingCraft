// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //核心UE运行环境下的要素
#include "GameFramework/Character.h"
#include "DCharacter.generated.h" //自己生成的，恶心代码


//便于编译效率
class UCameraComponent;
class USpringArmComponent;
class UDInteractionComponent;
class UAnimMontage;
class UDAttributeComponent;
class UDActionComponent;

UCLASS() //Part of UE Property System
class CHARMINGCRAFT_API ADCharacter : public ACharacter
{
	GENERATED_BODY() //确保放在第一行
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass; //stack 上的变量，在UE编辑器中被指定抛射物
	UPROPERTY(EditAnywhere, Category= "Attack")
	UAnimMontage* AttackAnim;
	FTimerHandle TimeHandle_PrimaryAttack;

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
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void PrimaryInteract();
	virtual void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	virtual void Dash_TimeElapsed();
	virtual void SprintStart();
	virtual void SprintStop();

	UPROPERTY(VisibleAnywhere) // 把SpringArmComp暴露给编辑器中的蓝图和各个部分
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	UDInteractionComponent* InteractionComp;


	/*
	 *	属性组件
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UDAttributeComponent* AttributeComp;

	/*
	 *	AbilityComponent System
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UDActionComponent* ActionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UCharacterMovementComponent* MovementComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
