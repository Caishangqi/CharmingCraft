// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerState.h"

int32 ADPlayerState::GetCredits() const
{
	return Credits;
}

bool ADPlayerState::AddCredit(int32 Delta)
{
	if (!ensure(Delta >= 0))
	{
		return false;
	}
	Credits += Delta;
	OnCreditsChanged.Broadcast(this, Credits, Delta);
	return true;
}

bool ADPlayerState::RemoveCredit(int32 Delta)
{
	if (!ensure(Delta >= 0))
	{
		return false;
	}
	//如果积分少于要扣除的量，那么是不被允许的
	if (Credits < Delta)
	{
		return false;
	}
	Credits -= Delta;
	OnCreditsChanged.Broadcast(this, Credits, Delta);
	return true;
}
