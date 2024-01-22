// Fill out your copyright notice in the Description page of Project Settings.


#include "DActionComponent.h"
#include "DAction.h"
#include "DCharacter.h"
#include "CharmingCraft/Core/Log/Logging.h"

// Sets default values for this component's properties
UDActionComponent::UDActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogChamingCraftItem, Display, TEXT("(+) UDActionComponent::UDActionComponent()"));

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

	for (auto Pair : DefaultBindAction)
	{
		AddBindAction(Pair.Key, Pair.Value);
	}

	TObjectPtr<ADCharacter> Player = Cast<ADCharacter>(GetOwner());
	// ...
}

void UDActionComponent::OnRegister()
{
	Super::OnRegister();
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

void UDActionComponent::MainHandAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::MainHandAction()");
	// TODO 把每个武器对应的 Action 单独创建一个蓝图类，这个Action蓝图要与武器挂钩
	this->StartActionByName(Cast<ADCharacter>(GetOwner()), "MainHand");
}

void UDActionComponent::OffHandAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::OffHandAction()");
}


void UDActionComponent::SkillStandbyPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::StandbyPressed()");
	this->StartActionByName(Cast<ADCharacter>(GetOwner()), "Standby");
}

void UDActionComponent::SkillStandbyReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::StandbyReleased()");
	this->StopActionByName(Cast<ADCharacter>(GetOwner()), "Standby");
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

void UDActionComponent::AddBindAction(int32 index, TSubclassOf<UDAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UDAction* NewAction = NewObject<UDAction>(this, ActionClass);
	BindAction.Add(index, NewAction);
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

bool UDActionComponent::StartActionByIndex(AActor* Instigator, int32 index)
{
	if (BindAction[index])
	{
		if (BindAction[index]->bIsCooling)
		{
			FString FailedMsg = FString::Printf(
				TEXT("[x] Failed to run: %s Because it is cooling, Remain: %f"),
				*BindAction[index]->ActionName.ToString(), BindAction[index]->GetRemainCooldown());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
			return false;
		}

		if (!BindAction[index]->CanStart(Instigator))
		{
			FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *BindAction[index]->ActionName.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
		}
		BindAction[index]->StartAction(Instigator);
		return true;
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

void UDActionComponent::CastActionOne()
{
	StartActionByIndex(GetOwner(), 1);
}
