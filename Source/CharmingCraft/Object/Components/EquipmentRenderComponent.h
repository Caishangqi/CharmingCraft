// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentRenderComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipmentRenderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentRenderComponent();

	/* Helmet Render Socket */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Helmet Socket")
	UStaticMeshComponent* HelmetSocket;

	
	/* Chest Plate Render Socket */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Chestplate Socket")
	UStaticMesh* ChestBodyProtectSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Chestplate Socket")
	UStaticMesh* RightArmProtectionSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Chestplate Socket")
	UStaticMesh* LeftArmProtectionSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Chestplate Socket")
	UStaticMesh* RightArmGloveSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Chestplate Socket")
	UStaticMesh* LeftArmGloveSocket;


	/* Legging Render Socket */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Legging Socket")
	UStaticMesh* BaffleSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Legging Socket")
	UStaticMesh* LeftLegSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Legging Socket")
	UStaticMesh* RightLegSocket;


	/* Boot Render Socket */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Boot Socket")
	UStaticMesh* LeftBootSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Boot Socket")
	UStaticMesh* RightBootSocket;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
