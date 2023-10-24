// Fill out your copyright notice in the Description page of Project Settings.


#include "../Object/Class/Item/Weapon.h"


void UWeapon::OnItemInteract(UItemStack* InteractItemStack, AActor* Instigator, AActor * ItemActorEntity)
{
	Super::OnItemInteract(InteractItemStack, Instigator,ItemActorEntity);
}

void UWeapon::OnWeaponUse()
{
}


void UWeapon::OnWeaponHit(UItemStack* WeaponHit, AActor* Instigator, AActor * ItemActorEntity)
{
}
