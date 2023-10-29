// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "../Object/Components/ItemStack.h"
#include "CharmingCraft/Entity/Item/model/SwordActor.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "Components/ArrowComponent.h"

/* 不修改数据, 只读取和执行操作 原型物品模板类 */
USword::USword()
{
	// 设置苹果的默认属性
	DisplayName = FText::FromString("Sword");
	MaxStackSize = 1;
}


void USword::OnItemInteract(UItemStack* InteractItemStack, AActor* Instigator, AActor* ItemActorEntity)
{
	Super::OnItemInteract(InteractItemStack, Instigator, ItemActorEntity);
	SwordActor = Cast<ASwordActor>(ItemActorEntity);
	Player = Instigator;
	MappingItemStack = InteractItemStack;

	UE_LOG(LogTemp, Display, TEXT("(!) USword::OnItemInteract(UItemStack* InteractItemStack)"));
	UE_LOG(LogTemp, Display, TEXT("ItemMeta: %s"), *InteractItemStack->ItemMeta->GetClass()->GetName());


	Instigator->GetWorld()->GetTimerManager().SetTimer(SwordTraceTimer, this, &USword::OnWeaponUse, 0.05f, true);
}

void USword::OnWeaponUse()
{
	Super::OnWeaponUse();

	// TODO 考虑是否让武器只能对敌人造成一次伤害 蒙太奇 + 动画通知
	FVector Start = SwordActor->SwordTopArrow->GetComponentLocation();
	FVector End = SwordActor->SwordTopArrow->GetComponentLocation();

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
			// Handle the hit. For example:
			// AActor* HitActor = HitResult.GetActor();
			// Do something with the HitActor...
			UE_LOG(LogTemp, Display, TEXT("Hited Actor: %s"), *Hit.GetActor()->GetName());
		}
	}
}

void USword::OnWeaponHit(UItemStack* WeaponHit, AActor* Instigator, AActor* ItemActorEntity)
{
	Super::OnWeaponHit(WeaponHit, Instigator, ItemActorEntity);
}

void USword::EndItemInteract()
{
	Super::EndItemInteract();
	Player->GetWorld()->GetTimerManager().ClearTimer(SwordTraceTimer);
}
