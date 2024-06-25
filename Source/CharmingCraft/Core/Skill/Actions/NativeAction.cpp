// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/Skill/Actions/NativeAction.h"

#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "CharmingCraft/Core/Skill/Actions/ActionActor/BaseActionActor.h"

void UNativeAction::StartAction_Implementation(APawn* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	StartCoolDown();
	// Find the ActionComponent we belong to, and apply the tag to that
	UDActionComponent* Comp = GetOwningComponent(Instigator);
	Comp->ActiveGamePlayTags.AppendTags(GrantsTags);
	CachedInstigator = Instigator;
	bIsRunning = true;
}

void UNativeAction::StopAction_Implementation(APawn* Instigator)
{
	UDActionComponent* Comp = GetOwningComponent(Instigator);
	Comp->ActiveGamePlayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}

bool UNativeAction::CanStart_Implementation(APawn* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	const UDActionComponent* Comp = GetOwningComponent(Instigator);
	/* 如果在激活的标签中发现应该禁止的, 则禁止不能启动该动作。 */
	if (Comp->ActiveGamePlayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

UWorld* UNativeAction::GetWorld() const
{
	// Outer is set when creating action via NewObject<T>
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if (Comp)
	{
		return Comp->GetWorld();
	}
	else if (Handler)
	{
		return Handler->GetWorld();
	}
	return nullptr;
}


UDActionComponent* UNativeAction::GetOwningComponent(APawn* Owner) const
{
	if (Cast<UDActionComponent>(GetOuter()))
	{
		return Cast<UDActionComponent>(GetOuter());
	}
	else if (Handler)
	{
		return Handler;
	}
	else
	{
		return Cast<UDActionComponent>(Owner->GetComponentByClass(UDActionComponent::StaticClass()));
	}
}

bool UNativeAction::IsRunning() const
{
	return bIsRunning;
}

void UNativeAction::StartCoolDown()
{
	if (CoolDown != 0.0f)
	{
		bIsCooling = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Cooldown, this, &UNativeAction::CooldownFinished, CoolDown);
		OnCoolStart.Broadcast(CachedInstigator);
	}
}

void UNativeAction::CooldownFinished()
{
	bIsCooling = false;
	ResetCoolDown();
	OnCoolComplete.Broadcast(CachedInstigator);
}

void UNativeAction::ResetCoolDown()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Cooldown);
}

float UNativeAction::GetRemainCooldown()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle_Cooldown);
}

void UNativeAction::SetIsSelected(bool RHS_IsSelected)
{
	this->bIsSelected = RHS_IsSelected;
}

// 吴昕,你这么写就是对自己最大的不负责
FHitData UNativeAction::GetActionHitData_Implementation()
{
	// 如果你只是创建默认的结构体你就应该在子类让用户强制实现
	FHitData HitData;
	return HitData;
}
// 吴昕,你这么写就是对自己最大的不负责
FActionActorData UNativeAction::GetActionActorData_Implementation()
{
	FActionActorData ActionActorData;
	return ActionActorData;
}
