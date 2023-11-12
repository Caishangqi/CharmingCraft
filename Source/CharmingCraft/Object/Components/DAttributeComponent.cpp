// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeComponent.h"

#include "CharmingCraft/Object/Structs/Attribute/FPlayerAttribute.h"

// Sets default values for this component's properties
UDAttributeComponent::UDAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	HealthMax = Health = 100;
	AttackRange = 100;
	Damage = 2.0f;
	AbilityPower = 0.0f;
	Mana = 0.0f;
	Level = 1;
	CurrentLevelXP = 0.0f;
	Armour = 0;
	KnockBackResistance = 1;
	CriticalChance = 0;
	CriticalDamageEnhance = 0;
	AttackSpeedEnhance = 0.0f;
}


// Called when the game starts
void UDAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UDAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UDAttributeComponent::ApplyHealthChange(const float Delta)
{
	Health += Delta;
	//播放事件, 触发事件
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}

bool UDAttributeComponent::ApplyManaChange(float Delta)
{
	Mana += Delta;
	OnManaChanged.Broadcast(nullptr, this, Mana, Delta);
	return true;
}

FPlayerAttribute UDAttributeComponent::GetPlayerAttributeData()
{
	PlayerAttribute.Damage = Damage;
	PlayerAttribute.Armour = Armour;
	PlayerAttribute.Health = Health;
	PlayerAttribute.Level = Level;
	PlayerAttribute.Mana = Mana;
	PlayerAttribute.AbilityPower = AbilityPower;
	PlayerAttribute.CriticalChance = CriticalChance;
	PlayerAttribute.HealthMax = HealthMax;
	PlayerAttribute.AttackSpeedEnhance = AttackSpeedEnhance;
	PlayerAttribute.CriticalDamageEnhance = CriticalDamageEnhance;
	PlayerAttribute.KnockBackResistance = KnockBackResistance;
	PlayerAttribute.CurrentLevelXP = CurrentLevelXP;

	return PlayerAttribute;
}
