// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "CharmingCraft/Core/Attribute/FPlayerAttribute.h"
#include "CharmingCraft/Core/Damage/DamageHandler/DamageChain.h"
#include "CharmingCraft/Core/Save/Data/PersistentDataComponent.h"
#include "Components/ActorComponent.h"
#include "DAttributeComponent.generated.h"

//创建并且定义这个事件
/*
 *	在C++中，delegate（委托）是一种用于实现事件、回调和多播委托的编程模式。它允许您
 *	将函数指针或成员函数指针与特定的对象实例绑定在一起，从而实现函数的间接调用。
 *
 *	其中第一个参数是事件名称,后续每个参数以此为 参数类型 + 参数变量
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, APawn*, InstigatorPawn, UDAttributeComponent*,
                                              OwningComp, float, NewHealth, float, Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnManaChanged, AActor*, InstigatorActor, UDAttributeComponent*,
                                              OwningComp, float, NewHealth, float, Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitDataApply, FHitData, InwardHitData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChange, FPlayerAttribute, DeltaAttribute, UObject*, Source);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, Blueprintable))
class CHARMINGCRAFT_API UDAttributeComponent : public UPersistentDataComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDAttributeComponent();

public:
	// -- Attributes -- //
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float AttackRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Damage; // Self Attack Damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float AbilityPower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float HealthMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Mana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 Level;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float CurrentLevelXP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 Armour;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 MagicDefense;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 KnockBackResistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 CriticalChance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 CriticalDamageEnhance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 CriticalDamageDefenseEnhance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float AttackSpeedEnhance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	int32 InteractRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attributes")
	bool IsDead;
	// Called when the game starts
	virtual void BeginPlay() override;


	/* Internal Attribute Struct Data */
	UPROPERTY(BlueprintReadWrite)
	FPlayerAttribute PlayerAttribute;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable) //暴露这个事件
	FOnHealthChanged OnHealthChanged; // 构造这个事件

	UPROPERTY(BlueprintAssignable)
	FOnManaChanged OnManaChanged; // 构造这个事件

	UPROPERTY(BlueprintAssignable)
	FOnHitDataApply OnHitDataApply;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChange OnAttributeChange;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UDamageChain> DamageChain;

	UFUNCTION(BlueprintCallable, Category= "Attributes")
	bool ApplyHealthChange(APawn* InstigatorPawn, float Delta); // whether or not change apply

	bool ApplyManaChange(APawn* InstigatorPawn, float Delta); // whether or not change apply

	UFUNCTION(BlueprintCallable)
	void ApplyAttributeChange(FPlayerAttribute DeltaAttribute, UObject* Source);

	UFUNCTION(BlueprintCallable)
	void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	FPlayerAttribute GetPlayerAttributeData();

	UFUNCTION(BlueprintCallable)
	void SubmitHitData(FHitData HitData);

	/*!
	 *	PostInwardHitData receive HitData from PreInwardHitData and apply the HitData
	 *	that was modified to the Attribute of the components, after the actual attribute
	 *	modification, it should broadcast to Entity(Owner) DamageIndicator Component to
	 *	display HitData on screen
	 *	
	 *	@param ModifiedHitData Accept modified HitData from PreInwardHitData()
	 *	@return FHitData The HitData that was finalized and prepare broadcast to
	 *	UI related components
	 */
	UFUNCTION(BlueprintCallable)
	FHitData PostInwardHitData(FHitData ModifiedHitData);

	//Serialization
public:
	virtual TSharedPtr<FJsonObject> SerializeToJson() override;
	
	virtual UObject* LoadDataFromJson(TSharedPtr<FJsonObject> JsonObject) override;
};
