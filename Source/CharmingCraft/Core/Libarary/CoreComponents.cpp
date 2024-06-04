// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreComponents.h"

#include "Kismet/GameplayStatics.h"

UCharmingCraftInstance* UCoreComponents::GetGameInstance(UObject* Context)
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(Context));
}

UWorldManager* UCoreComponents::GetWorldManager(UObject* Context)
{
	return GetGameInstance(Context)->GetWorldManager();
}

UGameEventHandler* UCoreComponents::GetGameEventHandler(UObject* Context)
{
	return GetGameInstance(Context)->GetGameEventHandler();
}
