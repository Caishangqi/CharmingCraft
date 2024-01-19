// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction.h"

#include "CharmingCraft/Core/Skill/DActionComponent.h"

void UDAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	StartCoolDown();
	// Find the ActionComponent we belong to, and apply the tag to that

	UDActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGamePlayTags.AppendTags(GrantsTags);

	bIsRunning = true;
}

void UDAction::StopAction_Implementation(AActor* Instigator)
{
	UDActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGamePlayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

bool UDAction::CanStart_Implementation(AActor* Instigator)
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

	return nullptr;
}


UDActionComponent* UDAction::GetOwningComponent() const
{
	return Cast<UDActionComponent>(GetOuter());
}

bool UDAction::IsRunning() const
{
	return bIsRunning;
}

void UDAction::StartCoolDown()
{
	bIsCooling = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Cooldown, this, &UDAction::CooldownFinished, CoolDown);
}

void UDAction::CooldownFinished()
{
	bIsCooling = false;
	ResetCoolDown();
}

void UDAction::ResetCoolDown()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Cooldown);
}

float UDAction::GetRemainCooldown()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle_Cooldown);
}
