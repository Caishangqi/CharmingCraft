// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeStandardMeleeAction.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Item/Meta/Abstruct/IntegratedMeta.h"
#include "CharmingCraft/Core/Item/RenderActor/Abstract/EquipmentEntityActor.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"
#include "Components/ArrowComponent.h"

UNativeStandardMeleeAction::UNativeStandardMeleeAction()
{
	SkillType = EItemDynamicSkillSlot::SHIFT_INTERACT;
}

void UNativeStandardMeleeAction::StartAction_Implementation(APawn* Instigator)
{
	Super::StartAction_Implementation(Instigator);
}

void UNativeStandardMeleeAction::EndMeleeActionTrace_Implementation()
{
	CastInstigatorPlayer->GetWorld()->GetTimerManager().ClearTimer(TraceTimer);
	HitActors.Empty(0);
}

void UNativeStandardMeleeAction::OnActionHit_Implementation(AActor* HitEntity)
{
	
	FPlayerAttribute PlayerAttribute = Cast<UDAttributeComponent>(CastInstigatorPlayer->GetComponentByClass(UDAttributeComponent::StaticClass()))->GetPlayerAttributeData();

	FEquipmentAttribute EquipmentAttribute = Cast<UIntegratedMeta>(BindItemStack->ItemMeta)->EquipmentAttribute;

	FHitData HitData;

	HitData.InstigatorPawn = CastInstigatorPlayer;
	HitData.Damage = EquipmentAttribute.Damage + PlayerAttribute.Damage;
	HitData.MagicDamage = EquipmentAttribute.MagicDamage + PlayerAttribute.AbilityPower;
	HitData.CriticalDamage = EquipmentAttribute.CriticalDamage + PlayerAttribute.CriticalDamageEnhance;
	HitData.DamageResponse = EDamageResponse::HitReaction;

	// 如果随机数小于暴击率，则表示暴击
	HitData.IsCritic = URoguelikeAttributeLibrary::IsAttackCriticInt(
		EquipmentAttribute.CriticalChance + PlayerAttribute.CriticalChance);

	UE_LOG(LogTemp, Display, TEXT("Hite Data: Damage = %f bIsCritic  = %hhd MagicDamage = %f"), HitData.Damage,
		   HitData.IsCritic, HitData.MagicDamage);

	IDamageable::Execute_OnActionHit(HitEntity, CastInstigatorPlayer, HitData);
}

void UNativeStandardMeleeAction::MeleeActionTick_Implementation()
{
	FVector Start = ItemEntityActor->EquipmentBottomArrow->GetComponentLocation();
	FVector End = ItemEntityActor->EquipmentTopArrow->GetComponentLocation();

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(CastInstigatorPlayer); // Ignore
	float SphereRadius = 120.0f; // 例如，设置为120.0，您可以根据需要进行调整

	bool bHit = CastInstigatorPlayer->GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Visibility,
														FCollisionShape::MakeSphere(SphereRadius), CollisionParams);
	float LineDuration = 2.0f; // for example, make the sphere visible for 2 seconds
	FColor LineColor = FColor::Green;

	DrawDebugLine(CastInstigatorPlayer->GetWorld(), Start, End, LineColor, false, LineDuration, ECC_Visibility, 4.0f);
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
					OnActionHit(HitActor);
				}

				// 添加Actor到已击中集合中
				HitActors.Add(HitActor);
			}
		}
	}
}

void UNativeStandardMeleeAction::StartMeleeActionTrace_Implementation()
{
	GameInstance->GetGameEventHandler()->OnItemInteractEvent(CastInstigatorPlayer,BindItemStack);
	CastInstigatorPlayer->GetWorld()->GetTimerManager().
				SetTimer(TraceTimer, this, &UNativeStandardMeleeAction::MeleeActionTick, 0.01f, true);
}
