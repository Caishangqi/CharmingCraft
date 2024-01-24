// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuffModel.h"

#include "BuffInfo.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"
#include "CharmingCraft/Core/Log/Logging.h"

void UBaseBuffModel::Apply_Implementation(UBuffInfo* BuffInfo, FHitData& HitData)
{
	AttributeComponent = Cast<UDAttributeComponent>(
		BuffInfo->Target->GetComponentByClass(UDAttributeComponent::StaticClass()));
}

UBaseBuffModel::UBaseBuffModel()

{
	UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Call Constructor of UBaseBuffModel"));
}
