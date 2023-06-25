// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "DItemChest.generated.h"

UCLASS()
class CHARMINGCRAFT_API ADItemChest : public AActor, public IDGameplayInterface
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override; //原本接口不需要 _Implementation 但是UE模板要这样

	UPROPERTY(EditAnywhere) //现在可以在编辑器中编辑这个变量, 这个变量可以控制箱子开合pitch
	float TargetPitch;

protected:
	//箱子底部
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	//箱子顶部
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	ADItemChest();
};
