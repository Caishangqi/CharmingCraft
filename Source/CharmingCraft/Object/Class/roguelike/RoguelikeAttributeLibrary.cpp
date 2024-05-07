// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguelikeAttributeLibrary.h"

#include "NativePlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

bool URoguelikeAttributeLibrary::IsAttackCriticFloat(float CriticValue)
{
	int32 RandomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 99);
	return RandomNumber < CriticValue;
}

bool URoguelikeAttributeLibrary::IsAttackCriticInt(int32 CriticValue)
{
	int32 RandomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 99);
	return RandomNumber < CriticValue;
}

int URoguelikeAttributeLibrary::GetCriticalDamage(int32 SourceCriticalDamageEnhance,
                                                  int32 TargetCriticalDamageDefenseEnhance)
{
	const int CriticalDamage = SourceCriticalDamageEnhance - TargetCriticalDamageDefenseEnhance;
	if (CriticalDamage < 100)
	{
		return 100;
	}
	return CriticalDamage;
}

float URoguelikeAttributeLibrary::GetDamageReduce(int32 TargetProtect)
{
	return 100 / (100 + TargetProtect);
}

int URoguelikeAttributeLibrary::GetDamage(int32 SourceDamage, int32 TargetProtect, bool bIsCritic,
                                          int32 OnHitCriticalDamage)
{
	if (bIsCritic)
	{
		return ((SourceDamage * OnHitCriticalDamage) / 100) * GetDamageReduce(
			TargetProtect);
	}
	else
	{
		return SourceDamage * GetDamageReduce(TargetProtect);
	}
}
