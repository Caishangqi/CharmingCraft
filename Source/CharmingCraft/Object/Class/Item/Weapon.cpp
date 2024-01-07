// Fill out your copyright notice in the Description page of Project Settings.


#include "../Object/Class/Item/Weapon.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Object/Components/ItemStack.h"
#include "Kismet/KismetMathLibrary.h"

void UWeapon::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator, AActor* ItemActorEntity)
{
	Super::OnItemInteract(InteractItemStack, Instigator, ItemActorEntity);
}

void UWeapon::OnWeaponUse()
{
}


void UWeapon::OnWeaponHit(UItemStack* WeaponHit, APawn* Instigator, AActor* ItemActorEntity, AActor* HitEntity)
{
}

void UWeapon::EndItemInteract()
{
	Super::EndItemInteract();
	Player->GetWorld()->GetTimerManager().ClearTimer(SwordTraceTimer);
	HitActors.Empty(0);
}
