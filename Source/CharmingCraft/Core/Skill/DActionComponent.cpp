// Fill out your copyright notice in the Description page of Project Settings.


#include "DActionComponent.h"
#include "../Core/Skill/Actions/NativeAction.h"
#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Core/CraftComponent/ItemComponent/ItemActionComponent.h"

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
	for (TSubclassOf<UNativeAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}

	for (auto Pair : DefaultBindAction)
	{
		AddBindAction(Pair.Key, Pair.Value);
	}

	TObjectPtr<ANativePlayerCharacter> Player = Cast<ANativePlayerCharacter>(GetOwner());

	// Handle Event
	if (!GetGameEventHandler_Implementation()->OnActorOnEquipment.IsBound())
	{
		GetGameEventHandler_Implementation()->OnActorOnEquipment.AddDynamic(
			this, &UDActionComponent::OnActorOnEquipmentEvent);

		GetGameEventHandler_Implementation()->OnActorUnEquipment.AddDynamic(
			this, &UDActionComponent::OnActorUnEquipmentEvent);
	}


	// Bind Event
	FOnItemDynamicSkillBindDelegate OnItemDynamicSkillBind = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance())
	                                                         ->GetGameEventHandler()->OnItemDynamicSkillBind;
	if (!OnItemDynamicSkillBind.IsBound())
	{
		OnItemDynamicSkillBind.AddDynamic(this, &UDActionComponent::OnItemDynamicSkillBindEvent);
	}
}

void UDActionComponent::OnRegister()
{
	Super::OnRegister();
}

void UDActionComponent::OnActorOnEquipmentEvent(UObject* Instigator, UItemStack* OnEquipItem, int32 EquipIndex)
{
	UE_LOG(LogChamingCraftAction, Display,
	       TEXT("[⚔️]  Actor装备物品事件: 物品名称 <%s>\n"
		       "		准备将物品技能组件内的Action添加到组件内"), *OnEquipItem->ItemMeta->DisplayName);
	TArray<UNativeCraftComponent*> ActionComponents = OnEquipItem->GetObjectComponentsByClass_Implementation(
		UItemActionComponent::StaticClass());
	for (UNativeCraftComponent* ActionComponent : ActionComponents)
	{
		MappingItemActionToComponent(Cast<UItemActionComponent>(ActionComponent));
	}
}

void UDActionComponent::OnActorUnEquipmentEvent(UObject* Instigator, UItemStack* UnEquipItem, int32 EquipIndex)
{
	UE_LOG(LogChamingCraftAction, Display,
	       TEXT("[⚔️]  Actor卸载物品事件: 物品名称 <%s>\n"
		       "		准备将物品技能组件内的Action从组件内移除"), *UnEquipItem->ItemMeta->DisplayName);
	TArray<UNativeCraftComponent*> ActionComponents = UnEquipItem->GetObjectComponentsByClass_Implementation(
		UItemActionComponent::StaticClass());
	for (UNativeCraftComponent* ActionComponent : ActionComponents)
	{
		MappingItemActionToComponent(Cast<UItemActionComponent>(ActionComponent),true);
	}
}

UCharmingCraftInstance* UDActionComponent::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
}

UGameEventHandler* UDActionComponent::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}


UWorldManager* UDActionComponent::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
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

void UDActionComponent::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = ActiveGamePlayTags;
}


void UDActionComponent::AddAction(const TSubclassOf<UNativeAction> ActionClass)
{
	/* 安全的空指针判断 */
	if (!ensure(ActionClass))
	{
		return;
	}

	/* 实例化 UNativeAction, outer可以理解成包裹的类,这样在 UDAction中就可以
	 * .GetOuter()获取 UDActionComponent 了.
	 */
	UNativeAction* NewAction = NewObject<UNativeAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

void UDActionComponent::AddBindAction(int32 index, TSubclassOf<UNativeAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UNativeAction* NewAction = NewObject<UNativeAction>(this, ActionClass);
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
	for (UNativeAction* Action : Actions)
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
	// UE_LOG(LogChamingCraftAction, Display,
	//        TEXT("[⚔️]  尝试执行指定类型 <%s> 的所有技能 执行对象<%s>"),
	//        *StaticEnum<EItemDynamicSkillSlot>()->GetNameByValue(static_cast<int64>(ActionType)).ToString(),
	//        *Instigator->GetName());
	for (auto Action : Actions)
	{
		// UE_LOG(LogChamingCraftAction, Display,
		// 			   TEXT("	  尝试执行 <%s> 执行对象 <%s>"),
		// 			   *Action->ActionName.ToString(), *Instigator->GetName());
		if (Action->SkillType == ActionType)
		{
			if (Action->bIsCooling)
			{
				FString FailedMsg = FString::Printf(TEXT("[x] Failed to run: %s Because it is cooling, Remain: %f"),
				                                    *Action->ActionName.ToString(), Action->GetRemainCooldown());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				// UE_LOG(LogChamingCraftAction, Warning,
				// 	   TEXT("		尝试执行 <%s> 失败失败原因: 技能在冷却"),
				// 	   *Action->ActionName.ToString());
				continue;
			}
			else if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *Action->ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				// UE_LOG(LogChamingCraftAction, Warning,
				// 	   TEXT("		尝试执行 <%s> 失败失败原因: 技能在不能启用"),
				// 	   *Action->ActionName.ToString());
				continue;
			}
			else if (!Action->GetIsSelected())
			{
				// UE_LOG(LogChamingCraftAction, Warning,
				// 	   TEXT("		尝试执行 <%s> 失败失败原因: 物品技能没有被选中"),
				// 	   *Action->ActionName.ToString());
				continue;
			}
			else
			{
				Action->StartAction(Instigator);
				UE_LOG(LogChamingCraftAction, Display,
					   TEXT("[⚔️]  执行技能 <%s> 执行对象 <%s>"),
					   *Action->ActionName.ToString(), *Instigator->GetName());
			}

			
			//return true;
		}
	}
	return false;
}

bool UDActionComponent::StopActionByType(APawn* Instigator, EItemDynamicSkillSlot ActionType)
{
	for (UNativeAction* Action : Actions)
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

void UDActionComponent::OnItemDynamicSkillBindEvent(APawn* Instigator, UNativeAction* FromAction,
                                                    UNativeAction* TargetAction, UItemMeta* ContextMeta)
{
	// We only want to receive broadcast when the item is equipped
	if (ContextMeta->bIsEquipped)
	{
		// Remove the original action on item from the pool
		if (FromAction)
		{
			StopActionByName(Instigator, FromAction->ActionName);
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
	for (UNativeAction* Action : Actions)
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

bool UDActionComponent::MappingItemActionToComponent(UItemActionComponent* ItemActionComponent,
                                                     bool bSetToRemoveMapping)
{
	UE_LOG(LogChamingCraftAction, Display,
	       TEXT("[⚔️]  将物品技能组件 <%s> 的技能映射到Action数组中. 是否为移除映射操作: <%d> "),
	       *ItemActionComponent->ItemDynamicSkillName.ToString(), bSetToRemoveMapping);
	if (!ItemActionComponent->GetActionInstances().IsEmpty())
	{
		if (bSetToRemoveMapping)
		{
			for (UNativeAction* ActionInstance : ItemActionComponent->GetActionInstances())
			{
				Actions.Remove(ActionInstance);
				UE_LOG(LogChamingCraftAction, Warning,
				       TEXT("		(-) 将物品技能 <%s> 映射到Action数组中. 映射操作为(移除)"),
				       *ActionInstance->ActionName.ToString());
			}
		}
		else
		{
			for (UNativeAction* ActionInstance : ItemActionComponent->GetActionInstances())
			{
				ActionInstance->Handler = this;
				Actions.Add(ActionInstance);
				UE_LOG(LogChamingCraftAction, Warning,
				       TEXT("		(+) 将物品技能 <%s> 映射到Action数组中. 映射操作为(添加)"),
				       *ActionInstance->ActionName.ToString());
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

void UDActionComponent::CastActionOne()
{
	StartActionByIndex(Cast<APawn>(GetOwner()), 1);
}
