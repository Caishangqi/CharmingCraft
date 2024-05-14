// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "../Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Core/Item/RenderActor/Equipment/SwordEntityActorP5.h"
#include "CharmingCraft/Interface/Meta/character/HandMeta.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"

UHand::UHand()
{
	DisplayName = FText::FromString("Hand");
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::HAND;
	ItemMetaClass = UHandMeta::StaticClass();
	MaxStackSize = 1;
}
