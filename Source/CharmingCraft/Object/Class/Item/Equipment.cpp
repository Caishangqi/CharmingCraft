// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

#include "DCharacter.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Core/Item/RenderActor/Abstract/EquipmentEntityActor.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"
#include "CharmingCraft/Object/Structs/model/FEquipmentAttribute.h"
#include "Components/ArrowComponent.h"


void UEquipment::OnEquip(UObject* Instigator, UItemStack* OnEquipItem)
{
	// UE_LOG(LogChamingCraftAction, Display,
	//        TEXT("[⚔️]  UEquipment::OnEquip =		%s"),
	//        *Instigator->GetName());
	if (Instigator->IsA(ADCharacter::StaticClass()))
	{
		TObjectPtr<ADCharacter> PlayerCharacter = Cast<ADCharacter>(Instigator);
		if (!OnEquipItem->ItemMeta->BindItemDynamicSkill.IsEmpty())
		{
			PlayerCharacter->ActionComponent->AddItemDynamicSkills(OnEquipItem->ItemMeta);
		}
	}
}

void UEquipment::UnEquip(UObject* Instigator, UItemStack* UnEquipItem)
{
	if (Instigator->IsA(ADCharacter::StaticClass()))
	{
		TObjectPtr<ADCharacter> PlayerCharacter = Cast<ADCharacter>(Instigator);
		if (UnEquipItem->ItemMeta->ItemDynamicSkill)
		{
			PlayerCharacter->ActionComponent->RemoveItemDynamicSkills(UnEquipItem->ItemMeta);
		}
	}
}

void UEquipment::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator)
{
	Super::OnItemInteract(InteractItemStack, Instigator);
	Cast<UCharmingCraftInstance>(Instigator->GetGameInstance())->GetGameEventHandler()->OnItemInteractEvent(
		Instigator, InteractItemStack);
	ItemEntityActor = Cast<AEquipmentEntityActor>(InteractItemStack->ItemMeta->ItemEntityActor);
	Player = Instigator;
	MappingItemStack = InteractItemStack;

	UE_LOG(LogTemp, Display, TEXT("(!) USword::OnItemInteract(UItemStack* InteractItemStack)"));
	UE_LOG(LogTemp, Display, TEXT("ItemMeta: %s"), *InteractItemStack->ItemMeta->GetClass()->GetName());
	Instigator->GetWorld()->GetTimerManager().
	            SetTimer(TraceTimer, this, &UEquipment::OnEquipmentDuringUse, 0.01f, true);
}

void UEquipment::OnEquipmentDuringUse()
{
	// TODO 考虑是否让武器只能对敌人造成一次伤害 蒙太奇 + 动画通知
	FVector Start = ItemEntityActor->EquipmentBottomArrow->GetComponentLocation();
	FVector End = ItemEntityActor->EquipmentTopArrow->GetComponentLocation();

	TArray<FHitResult> HitResults;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player); // Ignore self

	float SphereRadius = 120.0f; // 例如，设置为120.0，您可以根据需要进行调整

	bool bHit = Player->GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Visibility,
	                                                    FCollisionShape::MakeSphere(SphereRadius), CollisionParams);

	//Draw debug sphere
	float LineDuration = 2.0f; // for example, make the sphere visible for 2 seconds
	FColor LineColor = FColor::Green;

	// Draw debug line
	DrawDebugLine(Player->GetWorld(), Start, End, LineColor, false, LineDuration, ECC_Visibility, 4.0f);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			// 检查Actor是否已经被击中
			if (!HitActors.Contains(HitActor) && HitActor)
			{
				// 如果这个Actor还没有被击中
				UE_LOG(LogTemp, Display, TEXT("Hited Actor: %s"), *HitActor->GetName());

				if (HitActor->Implements<UDamageable>())
				{
					OnEquipmentHit(MappingItemStack, Player, HitActor);
				}

				// 添加Actor到已击中集合中
				HitActors.Add(HitActor);
			}
		}
	}
}

void UEquipment::OnEquipmentHit(UItemStack* EquipmentItemStack, APawn* Instigator, AActor* HitEntity)
{
	// TODO: Put Damage Handle into separate class
	FPlayerAttribute PlayerAttribute = Cast<ADCharacter>(Instigator)->AttributeComp->GetPlayerAttributeData();

	FEquipmentAttribute EquipmentAttribute = Cast<UIntegratedMeta>(EquipmentItemStack->ItemMeta)->EquipmentAttribute;

	FHitData HitData;

	HitData.InstigatorPawn = Instigator;
	HitData.Damage = EquipmentAttribute.Damage + PlayerAttribute.Damage;
	HitData.MagicDamage = EquipmentAttribute.MagicDamage + PlayerAttribute.AbilityPower;
	HitData.CriticalDamage = EquipmentAttribute.CriticalDamage + PlayerAttribute.CriticalDamageEnhance;
	HitData.DamageResponse = EDamageResponse::HitReaction;

	// 如果随机数小于暴击率，则表示暴击
	HitData.IsCritic = URoguelikeAttributeLibrary::IsAttackCriticInt(
		EquipmentAttribute.CriticalChance + PlayerAttribute.CriticalChance);

	UE_LOG(LogTemp, Display, TEXT("Hite Data: Damage = %f bIsCritic  = %hhd MagicDamage = %f"), HitData.Damage,
	       HitData.IsCritic, HitData.MagicDamage);

	IDamageable::Execute_OnActionHit(HitEntity, Player, HitData);
}

void UEquipment::EndItemInteract()
{
	Super::EndItemInteract();
	Player->GetWorld()->GetTimerManager().ClearTimer(TraceTimer);
	HitActors.Empty(0);
}
