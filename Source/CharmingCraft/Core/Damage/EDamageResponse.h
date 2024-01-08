#pragma once
UENUM(BlueprintType)
enum class EDamageResponse: uint8
{
	HitReaction,
	Stagger,
	Stun,
	KnockBack
};
