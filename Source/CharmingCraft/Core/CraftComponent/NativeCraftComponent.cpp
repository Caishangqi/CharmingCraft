// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeCraftComponent.h"

bool UNativeCraftComponent::IsAllowMultipleInstance() const
{
	return bIsAllowMultipleInstance;
}

void UNativeCraftComponent::SetIsAllowMultipleInstance(bool bIsAllowMultipleInstance)
{
	this->bIsAllowMultipleInstance = bIsAllowMultipleInstance;
}

bool UNativeCraftComponent::IsActive() const
{
	return bIsActive;
}

void UNativeCraftComponent::SetIsActive(bool bIsActive)
{
	this->bIsActive = bIsActive;
}

UNativeCraftComponent::UNativeCraftComponent()
{
}
