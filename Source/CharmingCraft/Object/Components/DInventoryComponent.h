// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Structs/FDSlotStruct.h"
#include "Components/ActorComponent.h"
#include "DInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDInventoryComponent();

	/* 将物品添加到物品栏函数 */
	virtual void AddToInventory();
	/* 将物品从到物品栏移除函数 */
	virtual void RemoveFromInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Parameter")
	int InventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Inventory Parameter")
	TArray<FDSlotStruct> Content;

	/* Replicated 确保只有服务器可以更改该属性，并且更改完毕后复制到客户端 */

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
