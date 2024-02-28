// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "SwordMeta.generated.h"

class ASwordActor;
class UEquipPartSwordPommel;
class UEquipPartSwordHilt;
class UEquipPartSwordGuard;
class UEquipPartSwordFuller;
class UEquipPartSwordBlade;
/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API USwordMeta : public UWeaponMeta
{
	GENERATED_BODY()

public:
	USwordMeta();

	/* 属性 部件 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Sword Blade")
	UEquipPartSwordBlade* SwordBlade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Sword Fuller")
	UEquipPartSwordFuller* SwordFuller;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Sword Guard")
	UEquipPartSwordGuard* SwordGuard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Sword Hilt")
	UEquipPartSwordHilt* SwordHilt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Sword Pommel")
	UEquipPartSwordPommel* SwordPommel;
	

	/* 渲染2D */
	virtual AItemEntityActor* CreateItemEntityActor(const UObject* WorldContextObject) override;

public:
	void SetDefaultAssemble();
};
