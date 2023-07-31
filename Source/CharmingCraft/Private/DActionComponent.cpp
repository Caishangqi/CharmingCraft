// Fill out your copyright notice in the Description page of Project Settings.


#include "DActionComponent.h"

#include "DAction.h"


// Sets default values for this component's properties
UDActionComponent::UDActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDActionComponent::BeginPlay()
{
	Super::BeginPlay();
	/* 把从编辑器设置的 DefaultActions 中的内容添加到 Actions中
	 * @see UDActionComponent.Actions 内容
	 */
	for (TSubclassOf<UDAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
	// ...
}


// Called every frame
void UDActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGamePlayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);
	// ...
}

void UDActionComponent::AddAction(const TSubclassOf<UDAction> ActionClass)
{
	/* 安全的空指针判断 */
	if (!ensure(ActionClass))
	{
		return;
	}

	/* 实例化 UDAction, outer可以理解成包裹的类,这样在 UDAction中就可以
	 * .GetOuter()获取 UDActionComponent 了.
	 */
	UDAction* NewAction = NewObject<UDAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UDActionComponent::StartActionByName(AActor* Instigator, const FName ActionName)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UDActionComponent::StopActionByName(AActor* Instigator, const FName ActionName)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}
