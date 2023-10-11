// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //核心UE运行环境下的要素
#include "GameFramework/Character.h"
#include "DCharacter.generated.h" //自己生成的，恶心代码


class UEquipmentManagerComponent;
class UDInventoryComponent;
class UPostProcessComponent;
class ADPlayerAIController;
//便于编译效率
class UCameraComponent;
class USpringArmComponent;
class UDInteractionComponent;
class UAnimMontage;
class UDAttributeComponent;
class UDActionComponent;

/*
 * https://sketchfab.com/3d-models/minecraft-player-slim-4e9962a0a094494ab3e85cd688f3d74d
 */
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ADPlayerAIController* PlayerAIController;

public:
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

	/* Debug Input button */
	virtual void PrintDebugMessage();

	/* Inventory */


	UPROPERTY(VisibleAnywhere) // 把SpringArmComp暴露给编辑器中的蓝图和各个部分
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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

	/* 后期处理组件 */
	//UPROPERTY(VisibleAnywhere)
	//UPostProcessComponent* PostProcessComponent;

	/* 物品栏 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UDInventoryComponent* InventoryComponent;

	/* 装备管理器 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	UEquipmentManagerComponent* EquipmentManagerComponent;

	/* 槽位管理器 (可以考虑)*/
	// TODO 添加槽位管理组件，这些组件包括格雷StaticMeshComponent 对应的骨骼Socket

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
