// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeComponent.h"
#include "CharmingCraft/Core/Buff/BuffHandlerComponent.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"
#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDAttributeComponent::UDAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	HealthMax = Health = 100;
	AttackRange = 100;
	InteractRange = 200;
	Damage = 2.0f;
	AbilityPower = 0.0f;
	Mana = 0.0f;
	Level = 1;
	CurrentLevelXP = 0.0f;
	Armour = 0;
	KnockBackResistance = 1;
	CriticalChance = 0;
	CriticalDamageDefenseEnhance = 0;
	CriticalDamageEnhance = 0;
	AttackSpeedEnhance = 0.0f;
	IsDead = false;
	UE_LOG(LogTemp, Warning, TEXT("UDAttributeComponent::UDAttributeComponent() Create Owner: %s"),
	       *GetOuter()->GetName());
}


// Called when the game starts
void UDAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!OnAttributeChange.IsBound())
	{
		OnAttributeChange.AddDynamic(this, &UDAttributeComponent::ApplyAttributeChange);
	}

	if (!DamageChain)
	{
		// Apply DamageChain
		DamageChain = NewObject<UDamageChain>(this, "DamageChain")->InitializeChain();
	}

	if (!GameInstance->GamePlayLogicManager->OnPlayerJoin.IsBound())
	{
		GameInstance->GamePlayLogicManager->OnPlayerJoin.AddDynamic(this, &UDAttributeComponent::OnPlayerJoin);
	}
	
}


// Called every frame
void UDAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ... 
}

bool UDAttributeComponent::ApplyHealthChange(APawn* InstigatorPawn, const float Delta)
{
	Health += Delta;
	//播放事件, 触发事件
	UE_LOG(LogTemp, Display, TEXT("[+]  UDAttributeComponent::ApplyHealthChange: %f | Owner: %s"), Delta,
	       *GetOwner()->GetName());
	OnHealthChanged.Broadcast(InstigatorPawn, this, Health, Delta);
	return true;
}

bool UDAttributeComponent::ApplyManaChange(APawn* InstigatorPawn, float Delta)
{
	Mana += Delta;
	OnManaChanged.Broadcast(InstigatorPawn, this, Mana, Delta);
	return true;
}

void UDAttributeComponent::ApplyAttributeChange(FPlayerAttribute DeltaAttribute, UObject* Source)
{
	/* TODO: Consider use operate override &= */
	this->AttackRange += DeltaAttribute.AttackRange;
	this->Health += DeltaAttribute.Health;
	this->Damage += DeltaAttribute.Damage;
	this->HealthMax += DeltaAttribute.HealthMax;
	this->AbilityPower += DeltaAttribute.AbilityPower;
	this->Mana += DeltaAttribute.Mana;
	this->CurrentLevelXP += DeltaAttribute.CurrentLevelXP;
	this->Armour += DeltaAttribute.Armour;
	this->MagicDefense += DeltaAttribute.MagicDefense;
	this->KnockBackResistance += DeltaAttribute.KnockBackResistance;
	this->CriticalChance += DeltaAttribute.CriticalChance;
	this->CriticalDamageEnhance += DeltaAttribute.CriticalDamageEnhance;
	this->CriticalDamageDefenseEnhance += DeltaAttribute.CriticalDamageDefenseEnhance;
	this->AttackSpeedEnhance += DeltaAttribute.AttackSpeedEnhance;
	this->InteractRange += DeltaAttribute.InteractRange;
}

void UDAttributeComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	UE_LOG(LogTemp, Warning, TEXT("UDAttributeComponent::OnComponentDestroyed() Destroy Owner: %p"), GetOwner());
}

FPlayerAttribute UDAttributeComponent::GetPlayerAttributeData()
{
	PlayerAttribute.Damage = Damage;
	PlayerAttribute.Armour = Armour;
	PlayerAttribute.MagicDefense = MagicDefense;
	PlayerAttribute.Health = Health;
	PlayerAttribute.Level = Level;
	PlayerAttribute.Mana = Mana;
	PlayerAttribute.AbilityPower = AbilityPower;
	PlayerAttribute.CriticalChance = CriticalChance;
	PlayerAttribute.HealthMax = HealthMax;
	PlayerAttribute.AttackSpeedEnhance = AttackSpeedEnhance;
	PlayerAttribute.CriticalDamageEnhance = CriticalDamageEnhance;
	PlayerAttribute.CriticalDamageDefenseEnhance = CriticalDamageDefenseEnhance;
	PlayerAttribute.KnockBackResistance = KnockBackResistance;
	PlayerAttribute.CurrentLevelXP = CurrentLevelXP;
	return PlayerAttribute;
}

void UDAttributeComponent::SubmitHitData(FHitData HitData)
{
	TObjectPtr<UBuffHandlerComponent> InstigatorBuffHandlerComponent;
	TObjectPtr<UBuffHandlerComponent> TargetBuffHandlerComponent = Cast<UBuffHandlerComponent>(
		GetOwner()->GetComponentByClass(UBuffHandlerComponent::StaticClass()));

	if (HitData.InstigatorPawn)
	// Validation Check, because Instigator may unload (such as enemy in another level that is unload)
	{
		InstigatorBuffHandlerComponent = Cast<UBuffHandlerComponent>(
			HitData.InstigatorPawn->GetComponentByClass(UBuffHandlerComponent::StaticClass()));
	}

	if (InstigatorBuffHandlerComponent) // Attacker
	{
		for (auto BuffInstance : InstigatorBuffHandlerComponent->BuffList)
		{
			// If the Buff do have OnHit Effect
			if (BuffInstance->BuffData->OnHit)
			{
				BuffInstance->BuffData->OnHit.GetDefaultObject()->Apply(BuffInstance, HitData);
			}
		}
	}

	if (TargetBuffHandlerComponent) // Defender
	{
		for (auto BuffInstance : TargetBuffHandlerComponent->BuffList)
		{
			if (BuffInstance->BuffData->OnBeHit)
			{
				BuffInstance->BuffData->OnBeHit.GetDefaultObject()->Apply(BuffInstance, HitData);
			}
		}
	}

	DamageChain->HandleDamage(HitData);
}


FHitData UDAttributeComponent::PostInwardHitData(FHitData ModifiedHitData)
{
	OnHitDataApply.Broadcast(ModifiedHitData);
	return ModifiedHitData;
}

TSharedPtr<FJsonObject> UDAttributeComponent::SerializeToJson()
{
	TSharedPtr<FJsonObject> SerializeJson = Super::SerializeToJson();
	SET_JSON_FIELD_NUMBER(SerializeJson, AttackRange, AttackRange);
	SET_JSON_FIELD_NUMBER(SerializeJson, Damage, Damage);
	SET_JSON_FIELD_NUMBER(SerializeJson, AbilityPower, AbilityPower);
	SET_JSON_FIELD_NUMBER(SerializeJson, Health, Health);
	SET_JSON_FIELD_NUMBER(SerializeJson, HealthMax, HealthMax);
	SET_JSON_FIELD_NUMBER(SerializeJson, Mana, Mana);
	SET_JSON_FIELD_NUMBER(SerializeJson, Level, Level);
	SET_JSON_FIELD_NUMBER(SerializeJson, CurrentLevelXP, CurrentLevelXP);
	SET_JSON_FIELD_NUMBER(SerializeJson, Armour, Armour);
	SET_JSON_FIELD_NUMBER(SerializeJson, MagicDefense, MagicDefense);
	SET_JSON_FIELD_NUMBER(SerializeJson, KnockBackResistance, KnockBackResistance);
	SET_JSON_FIELD_NUMBER(SerializeJson, CriticalChance, CriticalChance);
	SET_JSON_FIELD_NUMBER(SerializeJson, CriticalDamageEnhance, CriticalDamageEnhance);
	SET_JSON_FIELD_NUMBER(SerializeJson, CriticalDamageDefenseEnhance, CriticalDamageDefenseEnhance);
	SET_JSON_FIELD_NUMBER(SerializeJson, AttackSpeedEnhance, AttackSpeedEnhance);
	SET_JSON_FIELD_NUMBER(SerializeJson, InteractRange, InteractRange);
	SET_JSON_FIELD_BOOL(SerializeJson, IsDead, IsDead);
	return SerializeJson;
}

UObject* UDAttributeComponent::LoadDataFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject)
	{
		AttackRange = GET_JSON_FIELD_NUMBER(JsonObject, AttackRange);
		Damage = GET_JSON_FIELD_NUMBER(JsonObject, Damage);
		AbilityPower = GET_JSON_FIELD_NUMBER(JsonObject, AbilityPower);
		Health = GET_JSON_FIELD_NUMBER(JsonObject, Health);
		HealthMax = GET_JSON_FIELD_NUMBER(JsonObject, HealthMax);
		Mana = GET_JSON_FIELD_NUMBER(JsonObject, Mana);
		Level = GET_JSON_FIELD_NUMBER(JsonObject, Level);
		CurrentLevelXP = GET_JSON_FIELD_NUMBER(JsonObject, CurrentLevelXP);
		Armour = GET_JSON_FIELD_NUMBER(JsonObject, Armour);
		MagicDefense = GET_JSON_FIELD_NUMBER(JsonObject, MagicDefense);
		KnockBackResistance = GET_JSON_FIELD_NUMBER(JsonObject, KnockBackResistance);
		CriticalChance = GET_JSON_FIELD_NUMBER(JsonObject, CriticalChance);
		CriticalDamageEnhance = GET_JSON_FIELD_NUMBER(JsonObject, CriticalDamageEnhance);
		AttackSpeedEnhance = GET_JSON_FIELD_NUMBER(JsonObject, AttackSpeedEnhance);
		InteractRange = GET_JSON_FIELD_NUMBER(JsonObject, InteractRange);
		IsDead = GET_JSON_FIELD_BOOL(JsonObject, IsDead);
	}

	return this;
}

void UDAttributeComponent::OnPlayerJoin(ACharacter* PlayerCharacter)
{
	if (GetOwner() == PlayerCharacter)
	{
		Deserialize_Implementation(GameInstance->GetSaveManager()->CurrentSaveNode.PlayerData->AttributeComponentData);
		UE_LOG(LogChamingCraftSave, Display, TEXT("	[📤] Load AttributeComponentData to Player: %s, Health: %f"),
		       *GetOwner()->GetName(), Health);
	}
}
