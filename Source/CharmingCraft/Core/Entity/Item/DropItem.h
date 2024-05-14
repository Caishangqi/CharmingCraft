// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/Interact/NativeInteractActor.h"
#include "DropItem.generated.h"

class UBoxComponent;
class UItemStack;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ADropItem : public ANativeInteractActor
{
	GENERATED_BODY()

public:
	ADropItem();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "Drop Item Properties")
	TObjectPtr<UItemStack> ItemStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropIconMesh;
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropModelMesh;
	// Collision for External Actor, because interact highlight and interact not handle by external actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* InvisibleCollision;

	// 用于控制旋转速度的变量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float RotationSpeed = 30.0f;

	// 用于控制上下移动速度的变量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float BobbingSpeed = 4.0f;

	// 用于控制上下移动幅度的变量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float BobbingAmplitude = 1.0f;


	void Initialize(UItemStack* PassItemStack, AActor * DropItemOwner);

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	// 内部变量，用于追踪上下移动的相位
	float BobbingPhase = 0.0f;
	float CurrentRotationAngle = 0.f;
	float MaxRotationAngle = 45.f;
	int32 RotationDirection = 1; // 初始方向
};
