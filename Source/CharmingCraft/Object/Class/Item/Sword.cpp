// Fill out your copyright notice in the Description page of Project Settings.
#include "Sword.h"
#include "DCharacter.h"
#include "../Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Core/Item/RenderActor/Equipment/SwordEntityActorP5.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Interface/Meta/model/SwordMeta.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"
#include "Components/ArrowComponent.h"

/* 不修改数据, 只读取和执行操作 原型物品模板类 */
USword::USword()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Sword");
	MaxStackSize = 1;
	ItemType = EItemType::EQUIPMENT;
	Material = EMaterial::SWORD;
	ItemMetaClass = USwordMeta::StaticClass();
	Socket = EEquipmentSocket::HAND;
	DescribeText = FText::FromString("A sword is an edged, bladed weapon intended for manual cutting or thrusting.");
}


void USword::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator, AActor* ItemActorEntity)
{
	Super::OnItemInteract(InteractItemStack, Instigator, ItemActorEntity);
	SwordActor = Cast<AEquipmentEntityActor>(InteractItemStack->ItemMeta->ItemEntityActor);
	Player = Instigator;
	MappingItemStack = InteractItemStack;

	UE_LOG(LogTemp, Display, TEXT("(!) USword::OnItemInteract(UItemStack* InteractItemStack)"));
	UE_LOG(LogTemp, Display, TEXT("ItemMeta: %s"), *InteractItemStack->ItemMeta->GetClass()->GetName());

	Instigator->GetWorld()->GetTimerManager().SetTimer(SwordTraceTimer, this, &USword::OnWeaponUse, 0.01f, true);
}

void USword::OnWeaponUse()
{
	Super::OnWeaponUse();

	// TODO 考虑是否让武器只能对敌人造成一次伤害 蒙太奇 + 动画通知
	FVector Start = SwordActor->EquipmentTopArrow->GetComponentLocation();
	FVector End = SwordActor->EquipmentTopArrow->GetComponentLocation();

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
			if (!HitActors.Contains(HitActor))
			{
				// 如果这个Actor还没有被击中
				UE_LOG(LogTemp, Display, TEXT("Hited Actor: %s"), *HitActor->GetName());

				if (HitActor->Implements<UDamageable>())
				{
					OnWeaponHit(MappingItemStack, Player, SwordActor, HitActor);
				}

				// 添加Actor到已击中集合中
				HitActors.Add(HitActor);
			}
		}
	}
}

void USword::OnWeaponHit(UItemStack* WeaponHit, APawn* Instigator, AItemEntityActor* ItemActorEntity, AActor* HitEntity)
{
	Super::OnWeaponHit(WeaponHit, Instigator, ItemActorEntity, HitEntity);

	FPlayerAttribute PlayerAttribute = Cast<ADCharacter>(Instigator)->AttributeComp->GetPlayerAttributeData();

	FEquipmentAttribute EquipmentAttribute = Cast<UWeaponMeta>(WeaponHit->ItemMeta)->EquipmentAttribute;

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

void USword::EndItemInteract()
{
	Super::EndItemInteract();
	Player->GetWorld()->GetTimerManager().ClearTimer(SwordTraceTimer);
	HitActors.Empty(0);
}
