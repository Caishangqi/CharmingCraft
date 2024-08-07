// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //核心UE运行环境下的要素
#include "GameplayTagAssetInterface.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "GameFramework/Character.h"
#include "NativePlayerCharacter.generated.h"


class UNavigationInvokerComponent;
class UEquipmentComponent;
class UBuffHandlerComponent;
class UInventoryComponent;
class UPostProcessComponent;
class ADPlayerAIController;
//便于编译效率
class UCameraComponent;
class USpringArmComponent;
class UDInteractionComponent;
class UAnimMontage;
class UDAttributeComponent;
class UCraftActionComponent;
/*
 * https://sketchfab.com/3d-models/minecraft-player-slim-4e9962a0a094494ab3e85cd688f3d74d
 */
UCLASS() //Part of UE Property System
class CHARMINGCRAFT_API ANativePlayerCharacter : public ACharacter, public IDamageable, public ICoreManagerInterface, public IGameplayTagAssetInterface
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
	ANativePlayerCharacter();
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
	

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) // 把SpringArmComp暴露给编辑器中的蓝图和各个部分
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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
	UCraftActionComponent* ActionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	TObjectPtr<UBuffHandlerComponent> BuffHandlerComponent;

	/* 后期处理组件 */
	//UPROPERTY(VisibleAnywhere)
	//UPostProcessComponent* PostProcessComponent;

	/* 物品栏 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Components")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	/* 装备栏 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Components")
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

	// AI navigation
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Components")
	TObjectPtr<UNavigationInvokerComponent>  NavigationInvokerComponent;

	/* 槽位管理器 (可以考虑)*/
	// TODO 添加槽位管理组件，这些组件包括格雷StaticMeshComponent 对应的骨骼Socket

protected:
	UPROPERTY(EditAnywhere, Category="Tags")
	FGameplayTagContainer GameplayTags;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGuid PlayerUUID;
	
// Implementation
public:
	
	virtual void HandleHealthChanged_Implementation(APawn* InstigatorPawn, UDAttributeComponent* OwningComp,
													float Health, float HealthDelta) override;
	virtual void HandleDeath_Implementation(APawn* InstigatorPawn) override;

	virtual void OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData) override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	
	virtual UDAttributeComponent* GetAttributeComponent_Implementation() override;

	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UWorldManager* GetWorldManager_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
};
