// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction.h"

void UDAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
}

void UDAction::StopAction_Implementation(AActor* Instigator)
{
}
