// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction.h"

#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "CharmingCraft/Core/Skill/Actions/ActionActor/BaseActionActor.h"

void UDAction::StartAction_Implementation(APawn* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	StartCoolDown();
	// Find the ActionComponent we belong to, and apply the tag to that

	UDActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGamePlayTags.AppendTags(GrantsTags);
	CachedInstigator = Instigator;
	bIsRunning = true;
}

void UDAction::StopAction_Implementation(APawn* Instigator)
{
	UDActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGamePlayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

bool UDAction::CanStart_Implementation(APawn* Instigator)
{
	if (IsRunning())
	{
		return false;
	}

	const UDActionComponent* Comp = GetOwningComponent();
	/* 如果在激活的标签中发现应该禁止的, 则禁止不能启动该动作。 */
	if (Comp->ActiveGamePlayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

UWorld* UDAction::GetWorld() const
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


UDActionComponent* UDAction::GetOwningComponent() const
{
	if (Cast<UDActionComponent>(GetOuter()))
	{
		return Cast<UDActionComponent>(GetOuter());
	}
	else
	{
		return Handler;
	}
}

bool UDAction::IsRunning() const
{
	return bIsRunning;
}

void UDAction::StartCoolDown()
{
	if (CoolDown != 0.0f)
	{
		bIsCooling = true;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Cooldown, this, &UDAction::CooldownFinished, CoolDown);
		OnCoolStart.Broadcast(CachedInstigator);
	}
	
}

void UDAction::CooldownFinished()
{
	bIsCooling = false;
	ResetCoolDown();
	OnCoolComplete.Broadcast(CachedInstigator);
}

void UDAction::ResetCoolDown()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Cooldown);
}

float UDAction::GetRemainCooldown()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle_Cooldown);
}

FActionActorData UDAction::GetActionActorData_Implementation()
{
	FActionActorData ActionActorData;
	return  ActionActorData;
}
