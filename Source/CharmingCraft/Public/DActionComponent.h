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

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
