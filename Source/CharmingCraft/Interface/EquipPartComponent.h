// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipPartComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipPartComponent();

	/* 属性 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Component Properties")
	FString ItemID; //锻造这个部件所用的材料
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Component Properties")
	int32 ItemNeedToForge; // 多少个材料才能锻造这个部件
	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		Category= "Naming")
	FString TypeSuffix;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Graphic")
	TObjectPtr<UTexture2D> PartIcon; //这个部件在锻造GUI中的图标

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Graphic")
	UStaticMesh* PartMesh; //
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
