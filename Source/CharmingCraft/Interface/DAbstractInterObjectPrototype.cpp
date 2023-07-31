// Fill out your copyright notice in the Description page of Project Settings.


#include "DAbstractInterObjectPrototype.h"


ADAbstractInterObjectPrototype::ADAbstractInterObjectPrototype()
{
	MinimumInteractRange = 10;
	bIgnoreRangeToInteract = false;
	bIgnoreRangeToInteract = true;
}

void ADAbstractInterObjectPrototype::Interact_Implementation(APawn* InstigatorPawn)
{
	IDGameplayInterface::Interact_Implementation(InstigatorPawn);
}
