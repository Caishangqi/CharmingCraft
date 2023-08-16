// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DAttributeComponent.generated.h"

//创建并且定义这个事件
/*
 *	在C++中，delegate（委托）是一种用于实现事件、回调和多播委托的编程模式。它允许您
 *	将函数指针或成员函数指针与特定的对象实例绑定在一起，从而实现函数的间接调用。
 *
 *	其中第一个参数是事件名称,后续每个参数以此为 参数类型 + 参数变量
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UDAttributeComponent*,
                                              OwningComp, float, NewHealth, float, Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnManaChanged, AActor*, InstigatorActor, UDAttributeComponent*,
                                              OwningComp, float, NewHealth, float, Delta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UDAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDAttributeComponent();

protected:
	// -- Attributes -- //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Mana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 Level;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float CurrentLevelXP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 Armour;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 KnockBackResistance;


	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable) //暴露这个事件
	FOnHealthChanged OnHealthChanged; // 构造这个事件

	UPROPERTY(BlueprintAssignable)
	FOnManaChanged OnManaChanged; // 构造这个事件


	UFUNCTION(BlueprintCallable, Category= "Attributes")
	bool ApplyHealthChange(float Delta); // whether or not change apply

	bool ApplyManaChange(float Delta); // whether or not change apply
};
