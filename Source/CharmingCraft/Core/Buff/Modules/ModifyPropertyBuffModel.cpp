// Fill out your copyright notice in the Description page of Project Settings.


#include "ModifyPropertyBuffModel.h"

#include "NativePlayerCharacter.h"
#include "CharmingCraft/Core/Buff/BuffInfo.h"


UModifyPropertyBuffModel::UModifyPropertyBuffModel()
{
}

void UModifyPropertyBuffModel::Apply_Implementation(UBuffInfo* BuffInfo, FHitData& HitData)
{
	Super::Apply_Implementation(BuffInfo, HitData);
	AttributeComponent->OnAttributeChange.Broadcast(PlayerAttributeDelta, BuffInfo);
}
