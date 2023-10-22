// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DActionComponent.generated.h"

/*
 *	Action Component Holds the actions we want to able to use
 *	The main goal of Action Component is to keep a list of actions
 */


class UDAction;
DECLARE_LOG_CATEGORY_EXTERN(CharmingCraft, Display, Display);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UDActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/*
	 *	GameTag System
	 *	We can not use forwards declaration because it is a struct and
	 *	the compiler need to know the size of the struct, if it is a
	 *	pointer(same size) it do not need to know
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Tags")
	FGameplayTagContainer ActiveGamePlayTags;

	UFUNCTION(BlueprintCallable, Category= "Actions")
	void AddAction(TSubclassOf<UDAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	// Sets default values for this component's properties
	UDActionComponent();

protected:
	/** Granted abilities at game start */
	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<UDAction>> DefaultActions;

	// List of actions
	UPROPERTY() // When we deal with pointers to actions, we want to let UE handle
	TArray<UDAction*> Actions;

	// 1 技能释放 函数 - 技能名称 Action
	// 2 技能释放 函数 - 技能名称 Action (SkillOne(), ActionName())
	TMap<FName, FName> KeyBindings;
	// 动态绑定按键到特定功能
	auto BindSkillToAction(FName Skill, FName ActionName) -> void;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	/* In build Character Default Skill */
	void MainHandAction();
	void OffHandAction();

	void SkillOne();
	void SkillTwo();
	void SkillThree();
	void SkillFour();

	void SkillStandbyPressed(); /* Shift */
	void SkillStandbyReleased(); /* Shift */
};
