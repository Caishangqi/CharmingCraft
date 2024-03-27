// Fill out your copyright notice in the Description page of Project Settings.


#include "DActionComponent.h"
#include "DAction.h"
#include "DCharacter.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

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

	// Bind Event
	Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance())->GetGameEventHandler()->OnItemDynamicSkillBind.
	                                                             AddDynamic(this, &UDActionComponent::OnItemDynamicSkillBindEvent);

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

bool UDActionComponent::AddItemDynamicSkills(UItemMeta* ItemMeta)
{
	UE_LOG(LogChamingCraftAction, Display,
	       TEXT("[⚔️]  UDActionComponent::AddItemDynamicSkills = %s"),
	       *ItemMeta->ItemDynamicSkill->ItemDynamicSkillName.ToString());

	for (auto ActionPairs : ItemMeta->BindItemDynamicSkill)
	{
		if (ensure(ActionPairs.Value))
		{
			UE_LOG(LogChamingCraftAction, Display,
			       TEXT("		[+] Add Action = %s"),
			       *ActionPairs.Value->ActionName.ToString());
			// TargetAction's outer is not ActionComponent, need set handler
			ActionPairs.Value->Handler = this;
			Actions.Add(ActionPairs.Value);
			
			// TODO: Consider start action that is buff type or aura
		}
	}
	return true;
}

bool UDActionComponent::RemoveItemDynamicSkills(UItemMeta* ItemMeta)
{
	UE_LOG(LogChamingCraftAction, Display,
	       TEXT("[⚔️]  UDActionComponent::RemoveItemDynamicSkills =	%s"),
	       *ItemMeta->ItemDynamicSkill->ItemDynamicSkillName.ToString());

	for (auto ActionPairs : ItemMeta->BindItemDynamicSkill)
	{
		if (ensure(ActionPairs.Value))
		{
			UE_LOG(LogChamingCraftAction, Warning,
			       TEXT("		[-] Remove Action = %s"),
			       *ActionPairs.Value->ActionName.ToString());
			// TODO: Consider Unbind the event delegate
			Actions.Remove(ActionPairs.Value);
		}
	}
	return true;
}

bool UDActionComponent::StartActionByName(APawn* Instigator, const FName ActionName)
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

bool UDActionComponent::StartActionByType(APawn* Instigator, EItemDynamicSkillSlot ActionType)
{
	for (auto Action : Actions)
	{
		if (Action && Action->SkillType == ActionType)
		{
			if (Action->bIsCooling)
			{
				FString FailedMsg = FString::Printf(TEXT("[x] Failed to run: %s Because it is cooling, Remain: %f"),
					*Action->ActionName.ToString(), Action->GetRemainCooldown());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				return false;
			}

			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *Action->ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UDActionComponent::StopActionByType(APawn* Instigator, EItemDynamicSkillSlot ActionType)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->SkillType == ActionType)
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

bool UDActionComponent::HasActionByType(EItemDynamicSkillSlot ActionType)
{
	for (const auto Element : Actions)
	{
		if (Element->SkillType == ActionType)
		{
			return true;
		}
	}
	return false;
}

void UDActionComponent::OnItemDynamicSkillBindEvent(APawn* Instigator, UDAction* FromAction, UDAction* TargetAction, UItemMeta* ContextMeta)
{
	// We only want to receive broadcast when the item is equipped
	if (ContextMeta->bIsEquipped)
	{
		// Remove the original action on item from the pool
		if (FromAction)
		{
			StopActionByName(Instigator,FromAction->ActionName);
			Actions.Remove(FromAction);
		}
		// Add new select action to action pool
		if (TargetAction)
		{
			// TargetAction's outer is not ActionComponent, need set handler
			TargetAction->Handler = this;
			Actions.Add(TargetAction);
			// TODO: Consider start action that is buff type or aura
		}
	
	}
}

bool UDActionComponent::StartActionByIndex(APawn* Instigator, int32 index)
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

bool UDActionComponent::StopActionByName(APawn* Instigator, const FName ActionName)
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
	StartActionByIndex(Cast<APawn>(GetOwner()), 1);
}
