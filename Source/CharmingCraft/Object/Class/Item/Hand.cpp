// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand.h"

#include "DCharacter.h"
#include "../Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Damage/IDamageable.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Object/Class/roguelike/RoguelikeAttributeLibrary.h"

UHand::UHand()
{
	DisplayName = FText::FromString("Hand");
	MaxStackSize = 1;
}

void UHand::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator, AActor* ItemActorEntity)
{
	Super::OnItemInteract(InteractItemStack, Instigator, ItemActorEntity);
	Player = Instigator;
	Character = Cast<ADCharacter>(Player);

	MappingItemStack = InteractItemStack;
	UE_LOG(LogTemp, Display, TEXT("(!) UHand::OnItemInteract(UItemStack* InteractItemStack)"));
	UE_LOG(LogTemp, Display, TEXT("ItemMeta: %s"), *InteractItemStack->ItemMeta->GetClass()->GetName());
	Instigator->GetWorld()->GetTimerManager().SetTimer(SwordTraceTimer, this, &UHand::OnWeaponUse, 0.01f, true);
}

void UHand::OnWeaponUse()
{
	Super::OnWeaponUse();
	FVector Start = Character->GetActorLocation();
	FVector End = Start + Character->GetActorForwardVector() * Character->AttributeComp->AttackRange;

	TArray<FHitResult> HitResults;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player); // Ignore self

	float SphereRadius = 40.0f; // 例如，设置为120.0，您可以根据需要进行调整

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

void UHand::OnWeaponHit(UItemStack* WeaponHit, APawn* Instigator, AActor* ItemActorEntity, AActor* HitEntity)
{
	Super::OnWeaponHit(WeaponHit, Instigator, ItemActorEntity, HitEntity);
	FPlayerAttribute PlayerAttribute = Character->AttributeComp->GetPlayerAttributeData();
	FHitData HitData;

	HitData.InstigatorPawn = Instigator;
	HitData.Damage = PlayerAttribute.Damage;
	HitData.MagicDamage = PlayerAttribute.AbilityPower;
	HitData.CriticalDamage = PlayerAttribute.CriticalDamageEnhance;

	HitData.IsCritic = URoguelikeAttributeLibrary::IsAttackCriticInt(PlayerAttribute.CriticalChance);

	UE_LOG(LogTemp, Display, TEXT("Hite Data: Damage = %f bIsCritic  = %hhd MagicDamage = %f"), HitData.Damage,
	       HitData.IsCritic, HitData.MagicDamage);
	IDamageable::Execute_OnActionHit(HitEntity, Player, HitData);
}

void UHand::EndItemInteract()
{
	Super::EndItemInteract();
}
