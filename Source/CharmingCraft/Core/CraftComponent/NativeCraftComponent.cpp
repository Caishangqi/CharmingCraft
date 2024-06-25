// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeCraftComponent.h"

bool UNativeCraftComponent::IsAllowMultipleInstance() const
{
	return bIsAllowMultipleInstance;
}

void UNativeCraftComponent::SetIsAllowMultipleInstance(bool RHS_bIsAllowMultipleInstance)
{
	this->bIsAllowMultipleInstance = RHS_bIsAllowMultipleInstance;
}

bool UNativeCraftComponent::IsActive() const
{
	return bIsActive;
}

void UNativeCraftComponent::SetIsActive(bool RHS_bIsActive)
{
	this->bIsActive = RHS_bIsActive;
}

void UNativeCraftComponent::PostInitProperties()
{
	UObject::PostInitProperties();
}

UNativeCraftComponent::UNativeCraftComponent()
{
}
