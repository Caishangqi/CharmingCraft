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


void UDActionComponent::BindSkillToAction(FName Skill, FName ActionName)
{
	// 添加或更新绑定
	KeyBindings.Add(Skill, ActionName);
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


void UDActionComponent::SkillOne()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::SkillOne()");
}

void UDActionComponent::SkillTwo()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::SkillTwo()");
}

void UDActionComponent::SkillThree()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::SkillThree()");
}

void UDActionComponent::SkillFour()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "UDActionComponent::SkillFour()");
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
